# b-file
A simple tool to I/O binary file with specific data type.

## Notice

This program is currently in development. 

### Get the Source Code & Compile

``` shell
$ git clone https://github.com/SardineFish/file-b.git
$ cd file-b
$ make
```

Then you can find the **file-b** in `build/`. 

### Usage

Run the **file-b** and open a file

```shell
$ ./file-b open <path-to-file>
```

Read data as specific type

```shell
file-b> read int
file-b> read string
```

Remove the last data output

```shell
file-b> remove
```

Get help

```shell
file-b> help
```



