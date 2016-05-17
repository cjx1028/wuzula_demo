//demo�������ڽ���wuzula��������¸��ֳ��ù��ܵ�ʹ��
//1�����ݿ���ɾ�Ĳ�
//�����ֶε�ʹ�ã����ĵĽ�������װ�������ݿ��Ӧ����ͨ������������ɵģ�
//�ַ������ò���
//
//��ε�����������
//��ε����ⲿ����
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
static const char * _gpcDemoSQL2 = "insert into tserver values ('demoid', 'DEMO����', 1, 5, '0100000', '50:50:50')";



// ����ÿһ��������Ӧ�ó��򣨶�̬���ӿ⣩������Ҫ�еģ���ʼ��ʱ����
extern "C" int _appSTART()
{
    loginfo("_appstart~");

    return 0;
}


extern "C" int bizDEMO01(CBpCtx & ctx, CMessage & rq0, CMessage & rs0)
{
    //���ݿ����
    //1��ʹ�����ԭ�����ķ�ʽ
    //��ѯһ����¼�ķ�ʽ
    SP_Row row;
    dao.select(row, _gpcDemoSQL0, "biz.term");
    M_THROW_MY_ERROR(row.null(), 44, "��ȡ�������� ");
    char * id = row->get("ID");
    char * name = row->get("NAME");
    int  max  = row->getInt("MAX");
    loginfo("id=[%s], name=[%s], max=[%d]", id, name, max);

    //��ѯ������¼�ķ�ʽ
    std::vector<SP_Row> rows;
    dao.select(0, rows, _gpcDemoSQL1);
    //����Ǵ�������������sql��Ҳ����ʹ�����·�ʽ
    // dao.select(0, rows, _gpcDemoSQL, "lalalala");
    for (int i=0; i<rows.size(); ++i){
        char * id = rows[i]->get("ID");
        char * name = rows[i]->get("NAME");
        loginfo(" in rows, row [%d], id=[%s], name=[%s]", i, id, name);
    }


    //update, ��ȻҲ������insert/delete
    //����������ʱĬ��commit
    //dao.update(_gpcDemoSQL2);

    //�������ͽ���
    //dao.beginXA();
    //dao.endXA();

    //2��ʹ��CDaoUtil��ʽ�������ݿ���������˽�һ���ķ�װ
    //ע�⣺CMessage��CField�������ͻ�������ͨ�á�
    //��ѯ
    CDaoUtil * pDU = CDaoUtil::instance();
    CMessage msg = new CMessage("test");
    msg.set("ID", 1);//���ݿ��ֶ���Ӧ��Ϊ��д
    msg.set("NAME", "test");
    SP_Row row1;
    pDU->find(msg, dao, "ttest", row1);
    row1->print();

    //merge
    //�����ݿ��¼�ϲ�����������
    pDU->mergeRow(row1, msg);
    msg.print();

    //update
    msg.set("NAME", "IamTest");
    //pDU->update(msg, dao, "ttest", "id, name", false, NULL, "ID"); 
    
    //insert
    msg.set("ID", 6);//���ݿ��ֶ���Ӧ��Ϊ��д
    msg.set("NAME", "�Ƴ���");
    //pDU->insert(msg, dao, "ttest");

    //delete
    msg.set("ID", 6);//���ݿ��ֶ���Ӧ��Ϊ��д
    msg.set("NAME", "�Ƴ���");
    //pDU->erase(msg, dao, "ttest", NULL, "ID");


    //������������
    

    //�������ݽṹ



    return 0;
}
