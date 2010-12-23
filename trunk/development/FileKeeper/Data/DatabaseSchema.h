#pragma once

const char gszCreateSql[] =
		"BEGIN TRANSACTION;\n"
		"--Tables\n"
		"CREATE TABLE User\n"
		"(\n"
		"    Name VARCHAR(64) PRIMARY KEY,\n"
		"    Password CHAR(32) NOT NULL, --Enhanced encripted MD5 Value \n"
		"    Desc VARCHAR(256)\n"
		");\n"

		"CREATE TABLE Prog\n"
		"(\n"
		"    Path VARCHAR(260) PRIMARY KEY,\n"
		"    Option INTEGER,     -- -1 ingnore\n"
		"    FootPrint CHAR(32), --MD5 Value\n"
		"    Desc VARCHAR(256)\n"
		");\n"

		"CREATE TABLE ForbidList\n"
		"(\n"
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
		"    Option INTEGER, --forbid option, -1 means forbidden all program\n"
		"    ProgPath VARCHAR(260),\n"
		"    Path VARCHAR(260),\n"
		"    FOREIGN KEY (ProgPath) REFERENCES Prog\n"
		");\n"

		"CREATE TABLE EncryptList\n"
		"(\n"
		"    Path VARCHAR(260) PRIMARY KEY,\n"
		"    UserName VARCHAR(64) NOT NULL,\n"
		"    FOREIGN KEY (UserName) REFERENCES User\n"
		");\n"

		"CREATE TABLE SystemConfig\n"
		"(\n"
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
		"    ProgName VARCHAR(64),\n"
		"    ProgVer VARCHAR(64)\n"
		"    --Other values....\n"
		");\n"

		"--Views\n"
		"CREATE VIEW PathForbid AS SELECT Path FROM ForbidList WHERE Option = -1;\n"
		"CREATE VIEW IngoreProg AS SELECT Path, FootPrint, Desc FROM Prog WHERE Option = -1;\n"

		"--Indexes\n"
		"CREATE INDEX User_Index ON User(Name);\n"
		"CREATE INDEX Prog_Index ON Prog(Path);\n"
		"CREATE INDEX ForbidList_Index_1 ON ForbidList(ProgPath);\n"
		"CREATE INDEX ForbidList_Index_2 ON ForbidList(Path);\n"
		"CREATE INDEX ForbidList_Index_3 ON ForbidList(Option);\n"
		"CREATE INDEX EncryptList_Index_1 ON EncryptList(Path);\n"
		"CREATE INDEX EncryptList_Index_2 ON EncryptList(UserName);\n"
		"COMMIT;\n";

const char gszDropSql[] =
		"BEGIN TRANSACTION;\n"
		"DROP TABLE User;\n"
		"DROP TABLE Prog;\n"
		"DROP TABLE ForbidList;\n"
		"DROP TABLE EncryptList;\n"
		"DROP TABLE SystemConfig;\n"
		"COMMIT;\n";

const char gszCleanSql[] =
		"BEGIN TRANSACTION;\n"
		"DELETE FROM User;\n"
		"DELETE FROM Prog;\n"
		"DELETE FROM ForbidList;\n"
		"DELETE FROM EncryptList;\n"
		"DELETE FROM SystemConfig;\n"
		"COMMIT;\n";
