__author__ = 'morta'

import yaml


class GrammarException(Exception):
    def __init__(self, message: str):
        self.msg = message


# TODO:
# Fájl létezik? Fájl betöltése.
# YML parse
# A mi szabályaink ellenőrzése + átalakítás, hogy innentől egyértelmű legyen
# Ha minden ok, Object visszaadása
def load_yml(filename: str) -> dict:
    file = open(filename, mode='r')
    defs = yaml.load(file)
    check_grammar(defs)
    file.close()
    return defs


def check_grammar(defs: dict):
    lexers = defs['lexers']
    if not lexers or type(lexers) is not list or len(lexers) == 0:
        raise GrammarException("There is not valid lexer defined!")
    #if lexers

    # TODO
    pass
