```markdown
# V4L2 Device Query Tool

A lightweight C application to query and display the capabilities of Video4Linux2 (V4L2) devices.
This tool retrieves information about supported video formats, frame sizes, and device inputs.
It helping developers understand their video capture hardware better.

## Features

- Display V4L2 device capabilities (driver, card, bus, version, and capabilities).
- List supported video formats.
- Enumerate supported frame sizes for a given pixel format.
- Show available device inputs.
- Detect if the device supports streaming capabilities.

## Prerequisites

Ensure you have the following installed on your system:

- GCC (GNU Compiler Collection)
- Linux kernel headers with V4L2 support
- A V4L2-compatible device (e.g., a webcam) connected to `/dev/video0`

## How to Build

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd v4l2-device-query
   ```

2. Compile the program:
   ```bash
   gcc -Wall v4l2_query.c -o v4l2_query
   ```

## Usage

1. Connect your V4L2-compatible device (e.g., a USB webcam).
2. Run the program:
   ```bash
   ./v4l2_query
   ```

### Sample Output
```
Driver Caps:
  Driver: "uvcvideo"
  Card: "USB Camera"
  Bus: "usb-0000:00:14.0-1"
  Version: 5.10.12
  Capabilities: 84200001

Device is capable of streaming.

Supported Video Formats:
  YUYV 4:2:2
  MJPEG

Supported Frame Sizes:
  640x480
  1280x720

Available Inputs:
  Camera Input
```

## File Structure

```
.
├── v4l2_query.c   # Main source code file
├── README.md      # Documentation file
```

## Contributing

Contributions are welcome! If you'd like to enhance this project, please fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

**Disclaimer**: This tool is meant for educational and debugging purposes. Always ensure that you have the necessary permissions to access and query any connected video device.
```
