<?php

class WikiController extends Controller
{
	
	public function actions()
	{
		return array(
			
		);
	}
	
	public function filters()
	{
		return array(
			'accessControl', // perform access control for CRUD operations
		);
	}

	public function accessRules()
	{
		return array(
			array('allow',  // allow all users
				'users'=>array('*'),
			),
		);
	}

	public function actionIndex() {
		$this->render('index');
	}
	
	public function actionWikiLeft() {
		$modules = Modules::model()->findAll();
		$typeList = array('内存', '字符串', '网络', '数据结构');
		$this->render('wikiLeft', array('modules'=>$modules, 'typeList'=>$typeList));
	}
	
	public function actionWikiTop() {
		$this->render('wikiTop');
	}
	
	public function actionWikiMain() {
		$id = Yii::app()->request->getQuery('id');
		if ($id == null) $id = 1;
		$module = Modules::model()->find('module_id=:module_id', array(':module_id'=>$id));
		if (empty($module)) exit("not exists!");
		$func = Func::model()->findAll('Module_ID=:Module_ID', array(':Module_ID'=>$id));
		$this->render('wikiMain', array('module'=>$module, 'func'=>$func));
	}
}