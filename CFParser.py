#!/usr/bin/python3
__author__ = 'morta'

import cli
import lexer


def main():
    input, output, name, definitions = cli.get_params()

    lexer.generate_dir(name)
    lexer.generate_qx(definitions)
    lexer.generate_main(input, output)      # Todo: ez igazából a parser kimenete lesz
    lexer.compile_quex()

    # parser
    # run


if __name__ == '__main__':
    main()

