#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libusb/libusb.h>

libusb_context *context = NULL;
libusb_device_handle *handle = NULL;

int main(int argc, char *argv[])
{
	int ret;
	unsigned short vid, pid;
	unsigned char reqtype, req;
	unsigned short val, idx, len;

	if (argc != 3) {
		printf("usage: compliance_mode [vid] [pid]\n");
		exit(EXIT_SUCCESS);
	}
	vid = (unsigned short)strtoul(argv[1], NULL, 16);
	pid = (unsigned short)strtoul(argv[2], NULL, 16);

	/* init libusb */
	ret = libusb_init(&context);
	if (ret) {
		printf("libusb_init failed: %s\n", libusb_error_name(ret));
		goto err_libusb_init;
	}

	/* open device */
	handle = libusb_open_device_with_vid_pid(context, vid, pid);
	if (!handle) {
		printf("failed to open device %04x:%04x\n", vid, pid);
		goto err_open_device;
	}

	reqtype = 0x23;	// host2device, class req, port
	req = 0x03;	// set feature
	val = 0x0005;	// port link state
	idx = 0x0a << 8 | 1;
	len = 0x0000;
	ret = libusb_control_transfer(handle, reqtype, req, val, idx, NULL, len, 2000);
	if (ret != len) {
		printf("set_feature request failed: %s\n", libusb_error_name(ret));
	}

	libusb_close(handle);
err_open_device:
	libusb_exit(context);
err_libusb_init:
	if (ret < 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
