--Tables
CREATE TABLE User
(
    Name VARCHAR(64) PRIMARY KEY,
    Password CHAR(32) NOT NULL, --Enhanced encripted MD5 Value 
    Desc VARCHAR(256)
);

CREATE TABLE Prog
(
    Path VARCHAR(260) PRIMARY KEY,
    Option INTEGER,     -- -1 ingnore
    FootPrint CHAR(32), --MD5 Value
    Desc VARCHAR(256)
);

CREATE TABLE ForbidList
(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Option INTEGER, --forbid option, -1 means forbidden all program
    ProgPath VARCHAR(260),
    Path VARCHAR(260),
    FOREIGN KEY (ProgPath) REFERENCES Prog
);

CREATE TABLE EncryptList
(
    Path VARCHAR(260) PRIMARY KEY,
    UserName VARCHAR(64) NOT NULL,
    FOREIGN KEY (UserName) REFERENCES User
);

CREATE TABLE SystemConfig
(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    ProgName VARCHAR(64),
    ProgVer VARCHAR(64)
    --Other values....
);

--Views
CREATE VIEW PathForbid AS SELECT Path FROM ForbidList WHERE Option = -1;
CREATE VIEW IngoreProg AS SELECT Path, FootPrint, Desc FROM Prog WHERE Option = -1;

--Indexes
CREATE INDEX User_Index ON User(Name);
CREATE INDEX Prog_Index ON Prog(Path);
CREATE INDEX ForbidList_Index_1 ON ForbidList(ProgPath);
CREATE INDEX ForbidList_Index_2 ON ForbidList(Path);
CREATE INDEX ForbidList_Index_3 ON ForbidList(Option);
CREATE INDEX EncryptList_Index_1 ON EncryptList(Path);
CREATE INDEX EncryptList_Index_2 ON EncryptList(UserName);
