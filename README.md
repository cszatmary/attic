# attic

attic is a small program that allows you to use a local program globally.

#### How it works

attic will create an install directory and copy installed files there. This way it can keep track of what programs have been installed and easily remove them. By adding this install directory to your `PATH` you can run installed programs from anywhere.

#### Why?

I often create small programs to automate various tasks. I wanted a way to easily reuse these and have them available any time I need. So I created attic to make it easy to install and manage these programs.

## Quickstart

Install a program by running:

```
attic install <path>
```

The file must have executable permissions or the install will fail.

For information on additional commands and usage run:

```
attic --help
```

## Installation

### Binary installation

Coming soon.

### Manual installation

First clone the repo to get the source code:

```
git clone git@github.com:cszatmary/attic.git
```

Make sure you have [cmake](https://cmake.org/) installed. Then run:

```
mkdir build
cd build
cmake ..
```

This will configure cmake and generate the Makefile file.

Now build attic by running:

```
make
```

Now copy the `attic` executable to somewhere in your `PATH`.

Ex:

```
cp attic /usr/local/bin
```

Finally add attic's install path to your `PATH`.

```sh
export PATH="$(attic config INSTALL_PATH):$PATH"
```

## Configuration

attic can be configured through the `.atticrc.json` file located in your home directory. attic will automatically create an empty JSON file if one doesn't exist.

All fields are optional. Any missing fields will use the default value.

#### Install Path

The install path is where attic installs programs. The default install path is `~/.attic`. However, you can change it by setting the `installPath` field. A leading `~` is supported and will be expanded.

Ex:
```json
"installPath": "~/my/custom/path"
```

## License

attic is available under the [MIT License](https://github.com/cszatma/attic/tree/master/LICENSE).

## Contributing

Contributions are welcome. Feel free to open an issue or submit a pull request.
