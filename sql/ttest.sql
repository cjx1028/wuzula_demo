create table ttest(
id number(5),
name char(20)
)
                     
--必须要创建unique索引才可以使用CDaoUtils中的find功能
drop index idx_ttest;
create unique index idx_ttest on  ttest (
id
);


select * from ttest;
