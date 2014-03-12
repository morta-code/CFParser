__author__ = 'morta'
__version__ = '0.99b'

import sys
import getopt
import yaml
import yml_loader


# CFPArser
# Parancsori argumentumok értelmezése,
# Ha nincs, vagy help, akkor help kiírása
# Verzió
# ha hiányos, akkor default
# ha elégtelen, akkor help
# Visszatérés egy kész dict-tel.
def get_params() -> tuple:
    i = sys.stdin
    o = sys.stdout
    definitions = None
    name = ""

    if len(sys.argv) == 1 or "-h" in sys.argv:
        printhelp()
        sys.exit()
    elif "-v" in sys.argv:
        printver()
        sys.exit()
    else:
        try:
            name = sys.argv[1]
            # definitions = yaml.load(open(sys.argv[1]))
            # check_grammar()
            definitions = yml_loader.load_yml(name)
        except IOError:
            print("Not valid file: {}".format(sys.argv[1]))
            printhelp()
            sys.exit(2)
        except Exception as E:
            print(type(E))  # TODO exception szépítés (pl. a nyelvtanellenőrzésre)
            print("Given grammar file ({}) is not valid.").format(sys.argv[1])
            sys.exit(3)

        try:
            opts, args = getopt.getopt(sys.argv[2:], "i:o:")
        except getopt.GetoptError:
            printhelp()
            sys.exit(2)
        try:
            for opt, arg in opts:
                if opt == "-i":
                    i = open(arg, mode='r')
                elif opt == "-o":
                    o = open(arg, mode='w')
        except IOError:
            print("Not valid file: {}".format(input))
            printhelp()
            sys.exit(2)

    return i, o, name, definitions


def printhelp():
    print("Usage:\n\tcfparser [-h|-v]\n\tcfparser definition_file.yml [-i input] [-o output]")


def printver():
    print("CFParser {} © MÓRÉH Tamás, INDIG Balázs at PPKE ITK, 2014".format(__version__))
