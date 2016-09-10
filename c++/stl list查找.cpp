用STL通用算法find()在list中查找对象
list<char >::iterator FindIterator;
FindIterator = find(cList.begin(), cList.end(), 'c');
If (FindIterator == cList.end())
{
 printf("not find the char 'c'!");
}
else
{
 printf("%c", * FindIterator);
}
说明：如果没有找到指定的对象，就会返回cList.end()的值，找到了就返回一个指向对象iterator的指针。