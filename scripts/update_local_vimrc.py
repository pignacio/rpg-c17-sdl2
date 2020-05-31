#!/bin/env python3

import json
import re

CONAN_FLAGS_VARIABLE = "g:conan_flags"
LOCAL_VIMRC = ".lvimrc"

def main():
    conan_flags = json.load(open("conan_ycm_flags.json"))
    flags = conan_flags["flags"] + conan_flags["includes"] + conan_flags["defines"]
    contents = open(LOCAL_VIMRC).read()
    new_contents = re.sub(f"{CONAN_FLAGS_VARIABLE} = .*", f'{CONAN_FLAGS_VARIABLE} = "{" ".join(flags)}"', contents)

    print(new_contents)
    with open(LOCAL_VIMRC, "w") as vimrc:
        print(new_contents, file=vimrc)


if __name__ == "__main__":
    main()
