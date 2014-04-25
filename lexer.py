__author__ = 'morta'

import _io
import os

files = []


# generate qx-s
# generate main
# cache-elés
def generate_dir(name: str):
    if not os.path.exists(name):
        os.mkdir(name)
    os.chdir(name)


def generate_qx(definitions: dict):
    global files
    for i, lex in enumerate(definitions['lexers']):
        if definitions.get('define'):
            if lex['define']:   lex['define'].update(definitions['define'])
            else:               lex['define'] = definitions['define']
        if definitions.get('header'):
            if lex['header']:   lex['header'] = lex['header'] + "\n" + definitions['header']
            else:               lex['header'] = definitions['header']
        if definitions.get('body'):
            if lex['body']:     lex['body'] = lex['body'] + "\n" + definitions['body']
            else:               lex['body'] = definitions['body']
        if definitions.get('init'):
            if lex['init']:     lex['init'] = lex['init'] + "\n" + definitions['init']
            else:               lex['init'] = definitions['init']
        files.append(str(i)+'.qx')
        f = open(files[i], mode='w')
        fill_qx(f, lex)
        f.close()


def qx_list(filenames: list):
    global files
    files = filenames


# TODO itt az output kérdés nem tisztázott
def compile_main():
    l = len(files)
    sources = ""
    for i in range(1, l+1):
        sources += " cfl_{num}_cfl_{num}.cpp".format(num=i)
    os.popen("g++ -D CF_LEXERS_NUM={} -std=c++11 -I. -I $QUEX_PATH".format(l) +
             "{} main.cpp -o lexer.run".format(sources))


def compile_quex():
    for idx, qf in enumerate(files):
        os.popen("quex -i {f} -o cfl_{i}::cfl_{i} --token-id-prefix TKN_{i}_ ".format(f=qf, i=idx) +
                 "--buffer-element-type wchar_t --token-memory-management-by-user " +
                 "--token-queue-safety-border 1 --token-queue-size 3 --source-package .")
    # todo copy main.cpp here!



def fill_qx(qxfile: _io.FileIO, lexer: dict):
    # header
    if lexer.get('header'):
        qxfile.write("header\n{")
        qxfile.write(lexer['header'])
        qxfile.write("}\n\n")
    # define
    if lexer.get('define'):
        qxfile.write("define\n{")
        for key, val in lexer['define'].items():
            qxfile.write("\t{}\t{}\n".format(key, val))
        qxfile.write("}\n\n")
    # todo token?
    # body
    if lexer.get('body'):
        qxfile.write("body\n{")
        qxfile.write(lexer['body'])
        qxfile.write("}\n\n")
    # init
    if lexer.get('init'):
        qxfile.write("init\n{")
        qxfile.write(lexer['init'])
        qxfile.write("}\n\n")
    # todo modes
    for mod in lexer['modes']:
        if type(mod) is dict:
            pass
        else:  # mindenképpen str
            qxfile.write("start = {};\n".format(mod))
    pass