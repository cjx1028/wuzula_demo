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


extern "C" int bizDMOA01(CBpCtx & ctx, CMessage & rq0, CMessage & rs0)
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


    //�����ļ�
    //д�ļ�
    char filename[128];
    memset(filename, 0, sizeof(filename));
    snprintf(filename, sizeof(filename), "%s/logs/%s", _gpFrame->pcRunDir, "test.txt");

    char * content  = "hi, this is a test \n\
                             ���Ƕ�˵�й���";
    int iRet = putInFile(filename, "w", content, strlen(content));
    loginfo("putInFile, iRet=[%d], file=[%s]", iRet, filename);
    //�ж��ļ��Ƿ���� 
    char dir[128];
    char file[128];
    memset(dir, 0, sizeof(dir));
    sprintf(dir, "%s/", _gpFrame->pcRunDir);
    sprintf(file, "logs/%s", "test.txt");
    iRet = existFile( dir, file);
    loginfo("check if file is exist 1, iRet=[%d]", iRet);

    //���ļ�
    char * buf;
    getFileContent(filename, &buf);
    loginfo("�ļ����������£�");
    loginfo(buf);

    //ɾ���ļ�
    removeFile(dir, file);
    iRet = existFile( dir, file);
    loginfo("check if file is exist 2, iRet=[%d]", iRet);

    //������������
    //1�������ý��״��������Ҫ����response�����ô���msgCall��ʽ
    CBpStepSub step1(&ctx);
    CMessage & rq1 = *step1.pRqst_;
    rq1.copy(&msg,  "ID", "NAME", NULL);
    rq1.set("WHEREIAMFROM", "DMOA01");
    step1.call("cps", "DMOA02");
    step1.pRsp_->print();
    //2�������ý������д������ط������ݣ��Ҵ�ֻ��ת��������msgForward��ʽ
    step1.forward("cps", "DMOA03");

    //�������ݽṹ



    return 0;
}


extern "C" int bizDMOA02(CBpCtx & ctx, CMessage & rq0, CMessage & rs0)
{
    loginfo("this is in bizDMOA02 transaction");
    rq0.print();

    rs0.set("MSG", "GOOD JOB, YOU HAVE DONE IT!");

    return 0;
}


extern "C" int bizDMOA03(CBpCtx & ctx, CMessage & rq0, CMessage & rs0)
{
    loginfo("this is in bizDMOA03 transaction");
    
    rs0.set("MSG", "DMOA03 Finished!");

    return 0;
}
