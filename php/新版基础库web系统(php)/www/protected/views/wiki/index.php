<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Frameset//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title><?php echo Yii::app()->name; ?></title>
</head>
<frameset rows="18%,*" cols="*" frameborder="no" border="0" framespacing="0">
  <frame src="<?php echo CHtml::normalizeUrl(array('wiki/wikiTop'))?>" name="topFrame" scrolling="No" noresize="noresize" id="topFrame" title="topFrame" />
  <frameset rows="*" cols="20%,*" framespacing="0" frameborder="no" border="0">
    <frame src="<?php echo CHtml::normalizeUrl(array('wiki/wikiLeft'))?>" name="leftFrame" scrolling="No" noresize="noresize" id="leftFrame" title="leftFrame" />
    <frame src="<?php echo CHtml::normalizeUrl(array('wiki/wikiMain'))?>" name="mainFrame" id="mainFrame" title="mainFrame" />
  </frameset>
</frameset>
<noframes>
	<body>
	</body>
</noframes>
</html>