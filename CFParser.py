#!/usr/bin/python3
__author__ = 'morta'

import cli
import lexer
import sys


def main():
    input, output, name, definitions, qx_list = cli.get_params()

    if definitions:
        lexer.generate_dir(name)
        lexer.generate_qx(definitions)
    else:
        lexer.qx_list(qx_list)
    lexer.compile_quex()
    lexer.compile_main()

    # parser
    # run


if __name__ == '__main__':
    main()

