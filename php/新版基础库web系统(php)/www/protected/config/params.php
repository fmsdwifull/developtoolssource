<?php
return array(
	'adminMenu' => array(
		'模块管理'	=> array(
			array(
				'name'		=> '创建模块',
				'target'	=> 'dialog',
				'url'		=> 'modules/add',
				'rel'		=> 'modules_add',
				'mask'		=> 'true',
				'width'		=> 550,
				'height'	=> 520,
			),
			
			array(
				'name'		=> '模块管理',
				'target'	=> 'navTab',
				'url'		=> 'modules/index',
				'rel'		=> 'modules_index', 
			),
		),
		
		'函数管理'	=> array(
			array(
				'name'		=> '创建函数',
				'target'	=> 'dialog',
				'url'		=> 'func/add',
				'rel'		=> 'func_add',
				'mask'		=> 'true',
				'width'		=> 550,
				'height'	=> 520,
			),
			
			array(
				'name'		=> '函数管理',
				'target'	=> 'navTab',
				'url'		=> 'func/index',
				'rel'		=> 'func_index', 
			),
		),
		
		'系统管理'	=> array(
			array(
				'name'		=> '创建管理员',
				'target'	=> 'dialog',
				'url'		=> 'user/add',
				'rel'		=> 'user_add',
				'mask'		=> 'true',
			),
			
			array(
				'name'		=> '管理员管理',
				'target'	=> 'navTab',
				'url'		=> 'user/index',
				'rel'		=> 'user_index', 
			),
		),
	),
	
	'copyrightInfo'=>'Copyright &copy; 2013 by 天翼视讯',
	'numPerPage' => 30,
	'upload_dir' => './assets/upload/',
);