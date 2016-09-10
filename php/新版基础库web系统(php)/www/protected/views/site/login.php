<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title><?php echo Yii::app()->name; ?>-管理员登陆</title>
<style>
body{
	margin:0px;
	padding:0px;
	}
	
ul,li{
	margin:0px;
	padding:0px;
	list-style:none;
	}	

img{ border:none;}
.dl_box{
	width:950px;
	margin:0 auto;
	}
	
.top_nr{
    background-color:#3333FF;
	height:218px;
	width:950px;
	}
	
.top_nr01{
	width:300px;
	height:58px;
	float:left;
	padding-top:158px;
	padding-left:150px;
	font:35px/58px "微软雅黑";
	color:#ffffff;
	text-align:left;

}
	
.conter_nr{
	background:url(<?php echo Yii::app()->request->baseUrl; ?>/static/images/c_bg02.jpg) no-repeat;
	height:169px;
	padding-left:492px;
	}
	
.conter_nr li{
	font-family:"微软雅黑";
	font-size:18px;
	color:#211714;
	padding-top:30px;
	}
	
	
.conter_nr li input{
	width:206px;
	height:34px;
	line-height:34px;
	border:1px solid #cccccc;
	vertical-align:middle;
	}	
.bottom_nr{	
	background:url(<?php echo Yii::app()->request->baseUrl; ?>/static/images/b_bg01.jpg) no-repeat;
	width:auto;
	height:240px;
	text-align:right;
	padding-right:204px;
	padding-top:13px;
	}
</style>
</head>
<body>
<form id="mf" name="mf" method="post" action="<?php echo CHtml::normalizeUrl(array('site/login')); ?>">
  <div class="dl_box">
 <div class="top_nr" > <div class="top_nr01"><?php echo Yii::app()->name; ?></div> </div>
   	<div class="conter_nr">	
   	<ul>   
      <li>
      	用户名：
      	<input id="loginname" maxLength=20 name="login[username]" value="<?php echo isset($_POST['login']['username']) ? $_POST['login']['username'] : '';?>"/> 
      </li>
      <li>密&nbsp;&nbsp;&nbsp;&nbsp;码：
      	<input id="password" type=password name="login[password]" vvalue="<?php echo isset($_POST['login']['password']) ? $_POST['login']['password'] : '';?>"/>
      </li>
		<?php
			if ($model->getErrors()) {
		?>
			<font color="red"><?php echo $model->getError('username') ? $model->getError('username') : $model->getError('password'); ?></font>
		<?php
			}
		?>
      </ul>
	 
      </div>
	  <div class="bottom_nr"><input type="image" src="<?php echo Yii::app()->request->baseUrl; ?>/static/images/dl_btn.jpg"/></div>
	  </div>
</form>
</body>
</html>