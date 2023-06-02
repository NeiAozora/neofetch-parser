# Parse Neofetch

Parse Neofetch is a command-line utility written in C++ for parsing and generating JSON data from Neofetch output. It allows you to extract system information and format it as JSON for further processing.

## Features

- Parse Neofetch output and generate JSON data.
- Customize input and output files.
- Optional JSON pretty print for formatted output.

## Table of Contents

- [Minimum C++ Standard](#minimum-c-standard)
- [Naming Convention](#naming-convention)
- [Platform Support](#platform-support)
- [Compiling the Project](#compiling-the-project)
- [Usage](#usage)
- [Options](#options)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)


## Minimum C++ Standard

Parse Neofetch requires a minimum of C++11 standard to compile and run.

## Naming Convention

The code follows the camelCase naming convention for functions and variables.

## Platform Support

Parse Neofetch is supported on the following platforms:

- macOS
- Linux
- Windows

## Compiling the Project

To compile Parse Neofetch, follow these steps:

1. Clone the repository
2. Navigate to the project directory:
```shell
cd neofetch-parser
```
3. Compile the code using a C++ compiler. For example, using `g++`:
```shell
g++ -std=c++11 -o parse_neofetch parse_neofetch.cpp
```
Note: The -std=c++11 flag specifies the C++11 standard.

The executable parse_neofetch will be generated. You can run it by executing:
```shell
./parse_neofetch [OPTIONS]
```

## Usage

```shell
parse_neofetch <filename> [OPTIONS]
```
specify the file name to load without including <>

## Options
* -o FILE, --output FILE: Specify the output file (default file name: parsed_result.json)
* --json-pretty: Format the JSON output with indentation and line breaks
* --help, -h: Display the help message

## Examples

retrieve the output and save it to neofetch_output.txt. 
You can name it anything you want.
```shell
neofetch > neofetch_output.txt
```

Parse Neofetch output from neofetch_output.txt and save the result to result.json:
```shell
parse_neofetch neofetch_output.txt -o result.json
```

Parse Neofetch output from the default file output and enable JSON pretty print:
```shell
parse_neofetch --json-pretty
``` 

## Contributing
Contributions are welcome! If you have any ideas, suggestions, or bug reports, please open an issue or submit a pull request.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

Feel free to modify and customize the README file to fit your project's specific needs.
