//demo程序，用于介绍wuzula开发框架下各种常用功能的使用
//1、数据库增删改查
//报文字段的使用（报文的解析和组装是在数据库对应表中通过数据配置完成的）
//字符串常用操作
//
//如何调用其他交易
//如何调用外部交易
//


#include "bpctx.h"
#include "bpstep.h"
#include "ifront.h"
#include "iframe.h"
#include "base.h"
#include "error.h"
#include "ifilepcker.h"
#include "ifiletransfer.h"
#include "idaoutil.h"

static const char * _gpcDemoSQL0 = "select * from tserver where id='%s' ";
static const char * _gpcDemoSQL1 = "select * from tserver ";
static const char * _gpcDemoSQL2 = "insert into tserver values ('demoid', 'DEMO测试', 1, 5, '0100000', '50:50:50')";



// 这是每一个独立的应用程序（动态链接库）都必须要有的，初始化时调用
extern "C" int _appSTART()
{
    loginfo("_appstart~");

    return 0;
}


extern "C" int bizDEMO01(CBpCtx & ctx, CMessage & rq0, CMessage & rs0)
{
    //数据库操作
    //1、使用相对原生语句的方式
    //查询一条记录的方式
    SP_Row row;
    dao.select(row, _gpcDemoSQL0, "biz.term");
    M_THROW_MY_ERROR(row.null(), 44, "获取不到数据 ");
    char * id = row->get("ID");
    char * name = row->get("NAME");
    int  max  = row->getInt("MAX");
    loginfo("id=[%s], name=[%s], max=[%d]", id, name, max);

    //查询多条记录的方式
    std::vector<SP_Row> rows;
    dao.select(0, rows, _gpcDemoSQL1);
    //如果是带有条件参数的sql，也可以使用如下方式
    // dao.select(0, rows, _gpcDemoSQL, "lalalala");
    for (int i=0; i<rows.size(); ++i){
        char * id = rows[i]->get("ID");
        char * name = rows[i]->get("NAME");
        loginfo(" in rows, row [%d], id=[%s], name=[%s]", i, id, name);
    }


    //update, 自然也包括了insert/delete
    //不操作事务时默认commit
    //dao.update(_gpcDemoSQL2);

    //事务开启和结束
    //dao.beginXA();
    //dao.endXA();

    //2、使用CDaoUtil方式，对数据库操作进行了进一步的封装
    //注意：CMessage和CField两种类型基本可以通用。
    //查询
    CDaoUtil * pDU = CDaoUtil::instance();
    CMessage msg = new CMessage("test");
    msg.set("ID", 1);//数据库字段名应都为大写
    msg.set("NAME", "test");
    SP_Row row1;
    pDU->find(msg, dao, "ttest", row1);
    row1->print();

    //merge
    //将数据库记录合并到数据域中
    pDU->mergeRow(row1, msg);
    msg.print();

    //update
    msg.set("NAME", "IamTest");
    //pDU->update(msg, dao, "ttest", "id, name", false, NULL, "ID"); 
    
    //insert
    msg.set("ID", 6);//数据库字段名应都为大写
    msg.set("NAME", "唐长老");
    //pDU->insert(msg, dao, "ttest");

    //delete
    msg.set("ID", 6);//数据库字段名应都为大写
    msg.set("NAME", "唐长老");
    //pDU->erase(msg, dao, "ttest", NULL, "ID");


    //调用其他交易
    

    //常用数据结构



    return 0;
}
