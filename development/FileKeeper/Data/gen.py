#!/usr/bin/env python

import sys

def usage():
    print 'gen.py schemafile hppfile'

def main():
    sql = sys.argv[1]
    hpp = sys.argv[2]
        
    res = '#pragma once\n\nconst char gszCreateSql[] =\n'
    drop = '\nconst char gszDropSql[] =\n'
    clean = '\nconst char gszCleanSql[] =\n'
    
    sqlfile = open(sql)
    sqls = sqlfile.readlines()
    empyt = 0
    for sentence in sqls:
        sentence = sentence[:-1]
        if sentence == "":
            res = res + '\n'
            empty = empty + 1
            continue
        create = sentence.lower().find('create')
        table = sentence.lower().find('table')
        if create != -1 and table != -1:
            strTmp = sentence[len('table') + table : ].strip()
            idx = strTmp.find('(')
            tablename = strTmp
            if idx != -1:
                tablename = strTmp[:idx].strip()
            drop = drop + '\t\t"DROP TABLE ' + tablename + ';\\r\\n"\n'
            clean = clean + '\t\t"DELETE FROM ' + tablename + ';\\r\\n"\n'
        res = res + '\t\t"' + sentence + '\\r\\n"\n'
        empty = 0
    res = res[:-(empty+1)]
    res = res + ';\n'
    drop = drop[:-(empty+1)]
    drop = drop + ';\n'
    clean = clean[:-(empty+1)]
    clean = clean + ';\n'
    sqlfile.close()
    
    hppfile = open(hpp, 'w')
    hppfile.write(res)
    hppfile.write(drop)
    hppfile.write(clean)
    hppfile.close()
    
if __name__ == '__main__':
    if len(sys.argv) != 3:
        usage()
        exit(-1)
    main()


