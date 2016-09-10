<?php

class FuncController extends Controller
{
	protected $navTabId = 'func_index';
	
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
			array('allow', // allow authenticated users to access all actions
				'users'=>array('@'),
			),
			array('deny',  // deny all users
				'users'=>array('*'),
			),
		);
	}
	
	public function actionIndex() {
		$numPerPage = Yii::app()->params['numPerPage'];
		$criteria = new CDbCriteria;
		$criteria->select = '*';
		$name = '';
		if (($name = Yii::app()->request->getPost('name')) != null) {
			$criteria->addSearchCondition('Function_Name', $name);
		}
		$module_id = '';
		if (($module_id = Yii::app()->request->getPost('module_id')) != null) {
			$criteria->addSearchCondition('Module_ID', $module_id);
		}
		
		$count = Func::model()->count($criteria);
		
		$pager = new CPage($count);
		$pager->pageVar = 'pageNum';
		$pager->pageSize = $numPerPage;
		$criteria->order = 'Function_ID asc';
		$currentPage = $pager->currentPage + 1;
		$pager->applyLimit($criteria);
		$list = Func::model()->findAll($criteria);
		$modulesArr = Modules::model()->findAll();
		$renderVars = array(
			'numPerPage'	=> $numPerPage,
			'list'			=> $list,
			'count'			=> $count,
			'currentPage'	=> $currentPage,
			'currentUrl'	=> CHtml::normalizeUrl(array('func/index')),
			'name'			=> $name,
			'module_id'		=> $module_id,
			'modulesArr'	=> $modulesArr,
		);
		$this->render('index', $renderVars);
	}
	
	public function actionAdd() {
		if (($data = Yii::app()->request->getPost('data')) != null) {
			$currentDate  = date('Y-m-d H:i:s', time());
			$func = new Func;
			$func->attributes = $data;
			$func->createdtime = $currentDate;
			$func->createdby = Yii::app()->user->uid;
			
			if($func->save())
			{	
				$_REQUEST['callbackType'] = 'closeCurrent';
				$this->success('创建函数成功!');
			} else {
				foreach ($func->errors as $error) {
					$this->error($error[0]);
				}
			}
		}
		$modulesArr = Modules::model()->findAll();
		$this->render('add', array('modulesArr'=>$modulesArr));
	}
	
	public function actionDel() {
		if (($id = Yii::app()->request->getQuery('id')) != null) {
			$count = Func::model()->deleteByPk($id);
			if ($count > 0) {
				$this->success('删除模块成功！');
			} else {
				$this->success('删除模块失败！');
			}
		} else {
			$this->error('数据缺失！');
		}
	}
	
	public function actionEdit() {
		if (($uid = Yii::app()->request->getQuery('id')) != null) {
			$list = Func::model()->findByPk($uid);
			if (empty($list)) {
				$this->error('模块不存在！');
			}
			$modulesArr = Modules::model()->findAll();
			$this->render('edit', array('data'=>$list, 'modulesArr'=>$modulesArr));
		} else if (($data = Yii::app()->request->getPost('data')) != null) {
			$func = Func::model();
			$attributes = $data;
			$func->updateByPk($data['Function_ID'], $attributes);
			$_REQUEST['callbackType'] = 'closeCurrent';
			$this->success('修改成功!');
		}
	}
	
	public function actionDetail() {
		if (($uid = Yii::app()->request->getQuery('id')) != null) {
			$list = Func::model()->findByPk($uid);
			if (empty($list)) {
				$this->error('模块不存在！');
			}
			$modulesArr = Modules::model()->findAll();
			$this->render('detail', array('data'=>$list, 'modulesArr'=>$modulesArr));
		}
	}
}