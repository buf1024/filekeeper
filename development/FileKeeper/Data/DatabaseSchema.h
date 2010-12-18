#pragma once

const char gszCreateSql[] =
		"CREATE TABLE User\r\n"
		"(\r\n"
		"    Name VARCHAR(64) PRIMARY KEY,\r\n"
		"    Password CHAR(32) NOT NULL, --Enhanced encripted MD5 Value \r\n"
		"    Desc VARCHAR(256)\r\n"
		");\r\n"

		"CREATE TABLE Prog\r\n"
		"(\r\n"
		"    Path VARCHAR(260) PRIMARY KEY,\r\n"
		"    FootPrint CHAR(32), --MD5 Value\r\n"
		"    Desc VARCHAR(256)\r\n"
		");\r\n"

		"CREATE TABLE ForbidList\r\n"
		"(\r\n"
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,\r\n"
		"    Option INTEGER, --forbid option, -1 means forbidden all program\r\n"
		"    ProgPath VARCHAR(260),\r\n"
		"    Path VARCHAR(260),\r\n"
		"    FOREIGN KEY (ProgPath) REFERENCES Prog\r\n"
		");\r\n"

		"CREATE TABLE EncryptList\r\n"
		"(\r\n"
		"    Path VARCHAR(260) PRIMARY KEY,\r\n"
		"    UserName VARCHAR(64) NOT NULL,\r\n"
		"    FOREIGN KEY (UserName) REFERENCES User\r\n"
		");\r\n"

		"CREATE TABLE SysConfig\r\n"
		"(\r\n"
		"    ID INTEGER PRIMARY KEY AUTOINCREMENT,\r\n"
		"    ProgName VARCHAR(64),\r\n"
		"    ProgVer VARCHAR(16)\r\n"
		"    --Other values....\r\n"
		");\r\n"

		"INSERT INTO SysConfig(ProgName, ProgVer) VALUES('FileKeeper', '1.0.0.0');\r\n";

const char gszDropSql[] =
		"DROP TABLE User;\r\n"
		"DROP TABLE Prog;\r\n"
		"DROP TABLE ForbidList;\r\n"
		"DROP TABLE EncryptList;\r\n"
		"DROP TABLE SysConfig;\r\n";

const char gszCleanSql[] =
		"DELETE FROM User;\r\n"
		"DELETE FROM Prog;\r\n"
		"DELETE FROM ForbidList;\r\n"
		"DELETE FROM EncryptList;\r\n"
		"DELETE FROM SysConfig;\r\n";
