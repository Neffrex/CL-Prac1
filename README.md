# Flex & Bison Simple Calculator

## What can this proyect do?
This tool serves as an interpret of a simple typed language

# Get started

## Requirements
To start using this tool you will need to first install the package requirements

You can do so by running the installation script located in the root directory of this proyect
```
sudo install.sh
```

Or installing the packages listed in the `requirements` file manually

## Using the tool
Once you have installed the requirement packages you can now run the `MakeFile` by doing one of the following commands:

Compile the tool
```
make
```

Running the tool with the default file
```
make run
```

Running the tool with an input file. You must change `foo` to the path of the desired file to use 
```
make run INPUT_FILE=foo
```

Clean the build
```
make clean
```

Run gdb on the target
```
make debug
```

# Notas de implementación
· Al dividir por cero resulta en <inf>:float
· Los Struct no están implementados
· Las expresiones aritmeticas no aceptan expresiones booleanas