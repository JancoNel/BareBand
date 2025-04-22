# BareBand

BareBand is a minimalistic diagnostic tool for monitoring and troubleshooting network performance, particularly focused on detecting issues with Wi-Fi, ISP connections, and cellular tower signals. It provides an easy way to identify common network issues with a simple and intuitive interface.

## Features

- **Wi-Fi Signal Monitoring:** Checks the strength of the Wi-Fi connection.
- **Ping Test:** Verifies network connectivity by pinging local and remote servers.
- **Cell Tower Diagnostics:** Collects LTE signal information to diagnose issues related to cellular towers.
- **Minimalistic Interface:** Simple and clear UI to display diagnostic results.

## Supported Systems

- Windows (Built with C++ and C++ Builder)

## Installation

1. Download the latest release from the [releases page](#).
2. Extract the files to a folder.
3. Run `BareBand.exe` to start the application.

## How to Use

- Launch the application.
- Press the "Diagnose" button to start the network diagnostic process.
- Results will display at the bottom of the interface, indicating whether your network is healthy or if there are issues with Wi-Fi, ISP, or cellular towers.

## Diagnostics Results

- **WIFI_ISSUE:** Indicates a local Wi-Fi problem.
- **ISP_DOWN:** Indicates a potential problem with the ISP or SIM card.
- **TOWER_PROBLEM:** Indicates a weak or fluctuating signal from the cellular tower.
- **ALL_GOOD:** Everything is functioning correctly.

## About the Project

BareBand was developed to help identify the root cause of internet connectivity issues, as I have dealt with internet problems from every angle—whether it's weak Wi-Fi, an unreliable ISP, or fluctuating cellular tower signals. This tool is my attempt to streamline the process of diagnosing these issues and easily pinpoint the source of the problem.

Additionally, this is my first C++ project built using RAD Studio. I developed it as a way to deepen my understanding of C++ while using RAD Studio for rapid application development. The tool combines my passion for network diagnostics with the technical challenge of working with C++ and RAD Studio.

## Development

This project was built with C++ using C++ Builder, and it leverages Windows API functions for network diagnostics. The UI is designed to be simple and minimalistic, focusing on functionality rather than aesthetic complexity.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

---

Feel free to submit bug reports or feature requests through the [Issues](https://github.com/JancoNel/BareBand/issues) page. Contributions are welcome!
