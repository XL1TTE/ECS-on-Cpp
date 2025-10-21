#include "IDbRecord.h"
#include "DataBase.h"
#include "World.h"

using namespace DB;

IDbRecord::IDbRecord()
{
    m_record = DataBase::GetInstance().m_dbWorld->CreateEntity();
    DataBase::GetInstance().AddRecord(m_record.lock());
}
