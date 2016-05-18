delete from tdlldeploy where serverid = 'biz.term';
delete from tdllpara where serverid = 'biz.term';
delete from tfldcopy where chnlid = 'term.i';
delete from tchnl where chnlid='term.i';
delete from tpckctrl where chnlid = 'term.i';
delete from troute where chnlid = 'term.i';
delete from tpck where id = 'trmvbs.DMOA01';
delete from trspcdmap where chnlid='term.i';

INSERT INTO tchnl(CHNLID, NAME, ISBINPCK, IOTYPE, ISPCKER, PCKWRAPPER, PCKIDXMODE, FLAGS, KEYFLDS1, KEYFLDS2, TIMEOUT, ID4RSPCD, RSPCD4OK, ID4RSPMSG, DEFAULTRSPCD, DEFAULTRSPMSG, ID4CHNLTRNCD)
  VALUES('term.i', '终端接入', 0, 'I', '11', 'trmwrapper', 'TT', '11000000', 'TranDate,SerSeqNo', 'null', 30, 'RSPCD', '000000', 'RSPMSG', 'CPS999', '系统故障！', 'null');
INSERT INTO tdlldeploy(DLLID, SERVERID, STARTLEVEL)
  VALUES('TCPi', 'biz.term', 9);
INSERT INTO tdlldeploy(DLLID, SERVERID, STARTLEVEL)
  VALUES('bizterm', 'biz.term', 5);
INSERT INTO tdlldeploy(DLLID, SERVERID, STARTLEVEL)
  VALUES('uc', 'biz.term', 4);
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'TCPi', 'chnlid', 'term.i');
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'TCPi', 'port', '13208');
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'TCPi', 'rcvrnum', '10');
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'termtocard', 'user', 'card');
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'termtocard', 'passwd', 'card@CPSDB');
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'termtocard', 'YL_SETTLE', '/ylqs/03170000');
INSERT INTO tdllpara(SERVERID, DLLID, ID, VALUE)
  VALUES('biz.term', 'TCPi', 'lenprepck', '8');
INSERT INTO tfldcopy(CHNLID, TRNCD, FLDID, COPYAS)
  VALUES('term.i', '*', 'HEAD/TRNCD', NULL);
INSERT INTO tpck(ID, CONVERT, PRE, POST, NAME, FILLSTYLE, FILLCHAR, TRIM, PCKMODE, MUST, OPT, REF, SIGNFLDID)
  VALUES('trmvbs.DMOA01', 'vbs', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO tpck(ID, CONVERT, PRE, POST, NAME, FILLSTYLE, FILLCHAR, TRIM, PCKMODE, MUST, OPT, REF, SIGNFLDID)
  VALUES('trmvbs.DMOA02', 'vbs', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO tpck(ID, CONVERT, PRE, POST, NAME, FILLSTYLE, FILLCHAR, TRIM, PCKMODE, MUST, OPT, REF, SIGNFLDID)
  VALUES('trmvbs.DMOA03', 'vbs', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO tpckctrl(CHNLID, TRNCD, CHNLTRNCD, PACK, UNPACK, BYEXPR, BYEXPR4UN)
  VALUES('term.i', '*', NULL, 'trmvbs.all', 'trmvbs.all', NULL, '''trmvbs.all''');
INSERT INTO troute(CHNLID, SYSID, TRNCD, DLLID, ROUTEFLDID, SERVERID)
  VALUES('*', 'cps', 'DMO', 'demo', NULL, 'biz.term');
-- 设置路由有几种方式，分别是 
--*,       系统号,   交易号 
--*,       系统号，  交易类（交易号前三位）
--渠道号， 系统号，  *
--*,       系统号，  *   这种方式还待后续验证

INSERT INTO trspcdmap(RSPCD, CHNLID, RSPMSGLIKE, CHNLRSPCD, CHNLRSPMSG)
  VALUES(0, 'term.i', '0', '000000', '交易成功');
INSERT INTO trspcdmap(RSPCD, CHNLID, RSPMSGLIKE, CHNLRSPCD, CHNLRSPMSG)
  VALUES(99, 'term.i', 'M001', '999999', '登陆用户密码错');
