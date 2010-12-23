#!/usr/bin/env python

import sys

def usage():
    print 'gen.py schemafile hppfile'

def main():
    sql = sys.argv[1]
    hpp = sys.argv[2]
        
    res = '#pragma once\n\nconst char gszCreateSql[] =\n\t\t"BEGIN TRANSACTION;\\n"\n'
    drop = '\nconst char gszDropSql[] =\n\t\t"BEGIN TRANSACTION;\\n"\n'
    clean = '\nconst char gszCleanSql[] =\n\t\t"BEGIN TRANSACTION;\\n"\n'
    
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
            drop = drop + '\t\t"DROP TABLE ' + tablename + ';\\n"\n'
            clean = clean + '\t\t"DELETE FROM ' + tablename + ';\\n"\n'
        res = res + '\t\t"' + sentence + '\\n"\n'
        empty = 0
    res = res + '\t\t"COMMIT;\\n";\n'    
    drop = drop + '\t\t"COMMIT;\\n";\n'    
    clean = clean + '\t\t"COMMIT;\\n";\n'
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


