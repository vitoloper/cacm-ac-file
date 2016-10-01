# cacm-ac-file

A modified version (fixed model calculation from file) of the arithmetic coding software by R.M. Neal.
It calculates an exact probability model from an input file to encode.

## Installation

Clone the repository and launch make to compile:

```sh
$ git clone https://github.com/vitoloper/cacm-exact-file.git cacm-exact-file
$ cd cacm-exact-file
$ make
```

## Usage

Use the following command to encode a file:

```sh
$ ./file_encode file-to-encode output-model-file > encoded-file
```

where `file-to-encode` is the input file to encode, `output-model-file` is the calculated model from the input file and `encoded-file` is the encoded output file.

Use the following command to decode a file:
```sh
$ ./file_decode input-model-file > decoded-file
```

where `input-model-file` is the probability model and `decoded-file` is the decoded output file.
