CREATE TABLE User
(
    Name VARCHAR(64) PRIMARY KEY,
    Password CHAR(32) NOT NULL, --Enhanced encripted MD5 Value 
    Desc VARCHAR(256)
);

CREATE TABLE Prog
(
    Path VARCHAR(260) PRIMARY KEY,
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

CREATE TABLE SysConfig
(
    ID INTEGER PRIMARY KEY AUTOINCREMENT
    ProgName VARCHAR(64),
    ProgVer VARCHAR(16),
    --Other values....
);

INSERT INTO SysConfig(ProgName, ProVer) VALUES('FileKeeper', '1.0.0.0');
