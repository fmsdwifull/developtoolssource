/****************************************************************
*
*   autojson文件夹		file1.txt file2.txt为测试文件
*
******************************************************************/
编译   gcc -o autojson autojson.c -lm

参数：
-c	  生成自动合成json串的代码
-p	  生成自动解析json串的代码
-s    表示需要解析的是字符串   s后必须紧接字符串    注：在命令行输入时 json_string的 ， “ 需要转义
-f    表示需要解析的是文件     f后必须紧接文件 

执行程序的方式是  	autojson  -cs  json_string   			
			 	autojson  -ps  json_string		

				autojson  -cf  file1.txt 	 
				autojson  -pf  file2.txt	

命令行可以输入的json字符串可以如下：  

{\"hello\":\"world\"}

{\"cmd_type\":\"0X70000012\"\,\"from\":\"FS\"\,\"to\":\"MS\"\,\"timestamp\":\"\"\,\"dev_id\":\"\"\,\"tasks\":[{\"APP_name\":\"live\"\,\"streaming_id\":\"111\"\,\"rtmpConcurrency\":\"1\"\,\"rtspConcurrency\":\"1\"\,\"hlsConcurrency\":\"1\"\,\"hlsTotalDownload\":\"2\"\,\"rtmpFlow\":\"1111\"\,\"rtspFlow\":\"11\"\,\"hlsFlow\":\"1233\"}\,{\"ip\":\"192\"\,\"mac\":\"abc\"}]\,\"work\":[{\"dir\":\"home\"\,\"etc\":\"usr\"}]}










/****************************************************************
*
*   json文件夹中为json格式的c++解析库
*
******************************************************************/
生成的代码必须配合json文件夹的c++库进行使用
json文件夹中的代码与原来json库有如下修改：     

json_parse.cpp
修改 do_parse()    	解析json 构建树时增加一个根节点
增加 xget_object_element_by_name() 		用于通过名字获取对象孩子的指针
增加 GetRootNode()   	获取根节点的函数

json_parse.h
增加上面三个函数的声明














