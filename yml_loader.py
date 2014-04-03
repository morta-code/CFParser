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

    for i, lex in enumerate(lexers):
        # mode to modes
        if lex.get('mode') and not lex.get('modes'):
            lex['modes'] = [{'one': lex['mode']}]
            del lex['mode']
        elif not lex.get('modes') and not lex.get('mode'):
            raise GrammarException("No modes defined in lexer #{}".format(i))
        elif lex.get('mode') and lex.get('modes'):
            raise GrammarException("Ambigous modes definition in lexer # {}".format(i))

        # modes are lists?
        if type(lex['modes']) is not list:
            raise GrammarException("The 'modes' of lexer #{} is not a list!".format(i))

        # start mode
        if len(lex['modes']) == 1:
            pass
        elif len(lex['modes']) == 2 and type(lex['modes'][1]) is str:
            del lex['modes'][1]
        elif len(lex['modes']) > 1 and type(lex['modes'][-1]) is not str:
            lex['modes'].append(list(lex['modes'][0].keys())[0])
    # TODO folytatás

