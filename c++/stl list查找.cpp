��STLͨ���㷨find()��list�в��Ҷ���
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
˵�������û���ҵ�ָ���Ķ��󣬾ͻ᷵��cList.end()��ֵ���ҵ��˾ͷ���һ��ָ�����iterator��ָ�롣