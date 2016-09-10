<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title><?php echo Yii::app()->name; ?></title>
<link href="<?php Yii::app()->clientScript->registerCssFile(Yii::app()->request->baseUrl.'/static/css/themes/default/style.css'); ?>" rel="stylesheet" type="text/css" media="screen"/>
<link href="<?php echo Yii::app()->request->baseUrl; ?>/static/css/themes/css/core.css" rel="stylesheet" type="text/css" media="screen"/>
<link href="<?php echo Yii::app()->request->baseUrl; ?>/static/css/themes/css/print.css" rel="stylesheet" type="text/css" media="print"/>
<link href="<?php echo Yii::app()->request->baseUrl; ?>/static/js/uploadify/css/uploadify.css" rel="stylesheet" type="text/css" media="screen"/>
<!--[if IE]>
<link href="<?php echo Yii::app()->request->baseUrl; ?>/static/css/themes/css/ieHack.css" rel="stylesheet" type="text/css" media="screen"/>
<![endif]-->

<!--[if lte IE 9]>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/speedup.js" type="text/javascript"></script>
<![endif]-->

<script src="<?php Yii::app()->clientScript->registerScriptFile(Yii::app()->request->baseUrl.'/static/js/jquery-1.7.2.js'); ?>" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/jquery.cookie.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/jquery.validate.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/jquery.bgiframe.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/xheditor/xheditor-1.2.1.min.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/xheditor/xheditor_lang/zh-cn.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/uploadify/scripts/jquery.uploadify.js" type="text/javascript"></script>

<!-- svg图表  supports Firefox 3.0+, Safari 3.0+, Chrome 5.0+, Opera 9.5+ and Internet Explorer 6.0+ -->
<script type="text/javascript" src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/chart/raphael.js"></script>
<script type="text/javascript" src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/chart/g.raphael.js"></script>
<script type="text/javascript" src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/chart/g.bar.js"></script>
<script type="text/javascript" src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/chart/g.line.js"></script>
<script type="text/javascript" src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/chart/g.pie.js"></script>
<script type="text/javascript" src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/chart/g.dot.js"></script>

<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.core.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.util.date.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.validate.method.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.regional.zh.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.barDrag.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.drag.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.tree.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.accordion.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.ui.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.theme.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.switchEnv.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.alertMsg.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.contextmenu.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.navTab.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.tab.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.resize.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.dialog.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.dialogDrag.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.sortDrag.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.cssTable.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.stable.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.taskBar.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.ajax.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.pagination.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.database.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.datepicker.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.effects.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.panel.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.checkbox.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.history.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.combox.js" type="text/javascript"></script>
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.print.js" type="text/javascript"></script>
<!--
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/bin/dwz.min.js" type="text/javascript"></script>
-->
<script src="<?php echo Yii::app()->request->baseUrl; ?>/static/js/dwz.regional.zh.js" type="text/javascript"></script>

<script type="text/javascript">
$(function(){
	DWZ.init("<?php echo Yii::app()->request->baseUrl; ?>/static/xml/config.xml", {
		loginUrl:"<?php echo CHtml::normalizeUrl(array('user/login'));?>", loginTitle:"用户登录",	// 弹出登录对话框
		statusCode:{ok:200, error:300, timeout:301}, //【可选】
		pageInfo:{pageNum:"pageNum", numPerPage:"numPerPage", orderField:"orderField", orderDirection:"orderDirection"}, //【可选】
		debug : false,	// 调试模式 【true|false】
		callback:function(){
			initEnv();
			$("#themeList").theme({themeBase:"<?php echo Yii::app()->request->baseUrl; ?>/static/css/themes"}); // themeBase 相对于index页面的主题base路径
		}
	});
});

</script>
</head>

<body scroll="no">
	<div id="layout">
		<div id="header">
			<div class="headerNav">
				
				<div class="nav" style="color:#fff;margin-right:15px;font-size:12px;">
					欢迎您，<?php echo Yii::app()->user->name;?> | <!--<a href="<?php echo CHtml::normalizeUrl(array('user/updateUserPwd'));?>" style="color:#fff;">修改密码</a> |--> <a href="<?php echo CHtml::normalizeUrl(array('site/logout'))?>" style="color:#fff;">退出</a>
				</div>
				<ul class="themeList" id="themeList">
					<li theme="default"><div class="selected">蓝色</div></li>
					<li theme="green"><div>绿色</div></li>
					<li theme="purple"><div>紫色</div></li>
					<li theme="silver"><div>银色</div></li>
					<li theme="azure"><div>天蓝</div></li>
				</ul>
			</div>
		</div>

		<div id="leftside">
			<div id="sidebar_s">
				<div class="collapse">
					<div class="toggleCollapse"><div></div></div>
				</div>
			</div>
			<div id="sidebar">
				<div class="toggleCollapse"><h2>管理菜单</h2><div>收缩</div></div>

				<div class="accordion" fillSpace="sidebar">
					
					<?php
						$sidebar = Yii::app()->params['adminMenu'];
							foreach ($sidebar as $keyBar=>$valBar) {
					?>
					<div class="accordionHeader">
						<h2><span>Folder</span><?php echo $keyBar; ?></h2>
					</div>
					<div class="accordionContent">
						<ul class="tree treeFolder">
							<?php
								foreach ($valBar as $key=>$val) {
									$htmlOption = $val;
									unset($htmlOption['name']);
									unset($htmlOption['url']);
							?>
								<li><?php echo CHtml::link($val['name'], CHtml::normalizeUrl(array($val['url'])), $htmlOption);?></li>
							<?php
								}
							?>
						</ul>
					</div>
					<?php
						}
					?>

				</div>
			</div>
		</div>

		<div id="container">
			<div id="navTab" class="tabsPage">
				<div class="tabsPageHeader">
					<div class="tabsPageHeaderContent"><!-- 显示左右控制时添加 class="tabsPageHeaderMargin" -->
						<ul class="navTab-tab">
							<li tabid="main" class="main"><a href="javascript:;"><span><span class="home_icon">我的主页</span></span></a></li>
						</ul>
					</div>
					<div class="tabsLeft">left</div><!-- 禁用只需要添加一个样式 class="tabsLeft tabsLeftDisabled" -->
					<div class="tabsRight">right</div><!-- 禁用只需要添加一个样式 class="tabsRight tabsRightDisabled" -->
					<div class="tabsMore">more</div>
				</div>
				<ul class="tabsMoreList">
					<li><a href="javascript:;">我的主页</a></li>
				</ul>
				<div class="navTab-panel tabsPageContent layoutBox">
					<div class="page unitBox">
						<div class="accountInfo">
							
						</div>
						<div class="pageFormContent" layoutH="80" style="margin-right:230px">
							
						</div>
						
						
					</div>
					
				</div>
			</div>
		</div>
	</div>
	<div id="footer"><?php echo Yii::app()->params['copyrightInfo'];?></div>
</body>
</html>