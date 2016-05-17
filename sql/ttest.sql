create table ttest(
id number(5),
name char(20)
)

drop index idx_ttest;
create unique index idx_ttest on  ttest (
id
);


select * from ttest;
