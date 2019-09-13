# hard-disk-sorting-HDS-with-cinstrant

B10601002 四資工二乙 廖品捷 主題: Disk scheduling
語言:c++ 以下為程式說明:
This program is tested on CENTOS and MacOS  Open up terminal to execute hds.exe (ex: ./hds.exe access.in 2 ) 
argv[0] hds.exe 
argv[1] inputfile’s name by path 
argv[2] Qos constraint
輸出:access.out紀錄改變後排序順序。  心得:
這個實作主要是要運算硬碟的排程，我的做法是用一個 table 紀錄 disk 的使用，並且透過 elevator 和 shortest path 和 insertion 的方式去掃描和判斷是否符合 constraint 的要求，更 多內容請看 hds.cpp 裡面有註解
