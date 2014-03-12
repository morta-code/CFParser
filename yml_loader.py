__author__ = 'morta'

import yaml


# TODO:
# Fájl létezik? Fájl betöltése.
# YML parse
# A mi szabályaink ellenőrzése + átalakítás, hogy innentől egyértelmű legyen
# Ha minden ok, Object visszaadása
def load_yml(filename: str) -> dict:
    file = open(str, mode='r')
    defs = yaml.load(file)
    check_grammar(defs)
    file.close()
    return defs


def check_grammar(defs: dict):
    # TODO
    pass
