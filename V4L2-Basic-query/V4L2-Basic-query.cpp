#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

static const char DEVICE[] = "/dev/video0";

int print_capabilities(int fd) {
    int ret;
    struct v4l2_capability videodev0caps = { 0 };

    ret = ioctl(fd, VIDIOC_QUERYCAP, &videodev0caps);
    if (ret == -1) {
        perror("Querying device capabilities");
        return errno;
    }

    printf("Driver Caps:\n"
        "  Driver: \"%s\"\n"
        "  Card: \"%s\"\n"
        "  Bus: \"%s\"\n"
        "  Version: %u.%u.%u\n"
        "  Capabilities: %08x\n",
        videodev0caps.driver,
        videodev0caps.card,
        videodev0caps.bus_info,
        (videodev0caps.version >> 16) & 0xFF,
        (videodev0caps.version >> 8) & 0xFF,
        (videodev0caps.version) & 0xFF,
        videodev0caps.capabilities);

    if (ioctl(fd, VIDIOC_QUERYCAP, &videodev0caps) == -1) {
        perror("Querying device status");
        return;
    }

    if (videodev0caps.capabilities & V4L2_CAP_STREAMING) {
        printf("\nDevice is capable of streaming.\n");
    }
    else {
        printf("\nDevice is not capable of streaming.\n");
    }

    return 0;
}

void show_supported_formats(int fd) {
    struct v4l2_fmtdesc formats = { 0 };
    formats.index = 0;
    formats.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    printf("\nSupported Video Formats:\n");
    while (ioctl(fd, VIDIOC_ENUM_FMT, &formats) == 0) {
        printf("  %s\n", formats.description);
        formats.index++;
    }
}

void show_supported_frame_sizes(int fd, uint32_t pixel_format) {
    struct v4l2_frmsizeenum frame_size = { 0 };
    frame_size.index = 0;
    frame_size.pixel_format = pixel_format;

    printf("\nSupported Frame Sizes:\n");
    while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frame_size) == 0) {
        if (frame_size.type == V4L2_FRMSIZE_TYPE_DISCRETE) {
            printf("  %dx%d\n", frame_size.discrete.width, frame_size.discrete.height);
        }
        frame_size.index++;
    }
}

void show_device_inputs(int fd) {
    struct v4l2_input input = { 0 };
    input.index = 0;

    printf("\nAvailable Inputs:\n");
    while (ioctl(fd, VIDIOC_ENUMINPUT, &input) == 0) {
        printf("  %s\n", input.name);
        input.index++;
    }
}

int main(void) {
    int fd = open(DEVICE, O_RDONLY);
    if (fd < 0) {
        perror(DEVICE);
        return errno;
    }

    print_capabilities(fd);
    show_supported_formats(fd);
    show_supported_frame_sizes(fd, V4L2_PIX_FMT_YUYV);
    show_device_inputs(fd);

    close(fd);
    return 0;
}
