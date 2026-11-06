
# Step 1: Set Up the Separate Folder and Virtual Environment


Create a dedicated directory for your project and initialize your virtual environment inside it.

```bash
# Create and move into your project workspace
mkdir my-esphome-dev && cd my-esphome-dev

# Create the virtual environment
python3 -m venv venv

# Activate the virtual environment
# On Linux/macOS:
source venv/bin/activate
# On Windows (cmd):
# venv\Scripts\activate.bat
```

# Step 2: Install ESPHome in the Virtual Environment

With your virtual environment activated, install ESPHome via pip. This ensures your compilation and validation tools run locally within this isolated environment.

```bash
pip install wheel
pip install esphome
```

# Step 3: Structure Your Component Folder

ESPHome requires a specific directory structure to map external components correctly. Inside your workspace, create a folder for your configuration and a subfolder for your custom code:
```text
my-esphome-dev/
├── venv/                       # Your virtual environment
├── test_node.yaml              # The YAML configuration file for your ESP device
└── custom_components/          # Separate folder for your custom development
    └── my_custom_sensor/       # Your specific component folder
        ├── __init__.py         # Required Python entry point
        ├── sensor.py           # Configuration schema and code generation logic
        ├── my_custom_sensor.h  # C++ Header file
        └── my_custom_sensor.cpp# C++ Source file
```

# Step 4: Link the Separate Folder in Your YAML

To tell ESPHome to look inside your separate development folder instead of its core library, use the external_components component in your test_node.yaml file.
You can use a relative path pointing directly to your separate directory:

```yaml
esphome:
  name: test-node

esp32:
  board: esp32dev

# Point ESPHome to your separate development folder
external_components:
  - source:
      type: local
      path: custom_components

# Implement your component using the exact folder name you created
sensor:
  - platform: my_custom_sensor
    name: "My Custom Live Sensor"
```

# Step 5: Compile and Run

Because ESPHome is installed inside your virtual environment, you can run normal CLI commands to validate, compile, and upload your code while editing your component files in real-time.
```bash
# Validate that your custom component schemas pass checks
esphome config test_node.yaml

# Compile only
esphome compile test_node.yaml

# Compile and flash the device
esphome run test_node.yaml
```

# Step 6: Quit virtual environment

```bash
deactivate
```