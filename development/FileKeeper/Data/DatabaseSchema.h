#pragma once

const char s_gszSql[] =
		"CREATE TABLE User"
		"("
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"    Name VARCHAR(64) NOT NULL,"
		"    Password CHAR(32) NOT NULL, --Enhanced encripted MD5 Value "
		"    Desc VARCHAR(256)"
		");"

		"CREATE TABLE Prog"
		"("
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"    Name VARCHAR(64) NOT NULL,"
		"    Path VARCHAR(260) NOT NULL,"
		"    FootPrint CHAR(32), --MD5 Value"
		"    Desc VARCHAR(256)"
		");"

		"CREATE TABLE ForbidList"
		"("
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"    Option INTEGER, --0 forbid all, othervalue forbid specific program"
		"    ProgID INTEGER,"
		"    Path VARCHAR(260),"
		"    FOREIGN KEY (ProgID) REFERENCES Prog"
		");"

		"CREATE TABLE EncryptList"
		"("
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"    UserID INTEGER,"
		"    Path VARCHAR(260),"
		"    FOREIGN KEY (UserID) REFERENCES User"
		");"

		"CREATE TABLE SysConfig"
		"("
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT"
		"    --Other values...."
		");";
