////////////////////////////////////////////////////////////////////////////////////////
// 
// Filekeeper Project
//  
//  
// FileName    : FileKeeperContext.h
// Purpose     : The FileKeeper Global Context
// Version     : 2010-12-23 (22:42) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Singleton.h"

class FileKeeperContext
    : public lgc::Singleton<FileKeeperContext>
{
public:
    FileKeeperContext(void);
    ~FileKeeperContext(void);
};
