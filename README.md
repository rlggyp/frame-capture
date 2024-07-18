# frame-capture

A tool for capturing frames from a camera, simplifying the process of collecting datasets.

## Features
- [x] **Dynamic Control:** Automatically gets control settings dynamically from the camera.
- [x] **Save Camera Configuration:** Save configuration settings to YAML files for future use.

## Usage
#### Install Dependencies:
```bash
sudo apt install libv4l-dev libyaml-cpp-dev libopencv-dev g++ gcc cmake make
```

#### Clone and Build the Program:
```bash
git clone https://github.com/rlggyp/frame-capture.git
cd frame-capture
mkdir build
cd build
cmake ../src
make
```

#### Run the Program:
```bash
./frame_capture <camera_id> <output_directory>
```

<div align="center">

| Key  | Description                                      |
|------|--------------------------------------------------|
| `r`  | Start/stop recording video.                      |
| `s`  | Capture the current frame.                       |
| `w`  | Write configuration settings to YAML file.       |
| `ESC`| Exit the program.                                |

</div>

## Contributing
Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE). See the LICENSE file for details.