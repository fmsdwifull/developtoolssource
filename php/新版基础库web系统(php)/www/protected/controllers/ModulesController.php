<?php

class ModulesController extends Controller
{
	protected $navTabId = 'modules_index';
	
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
			$criteria->addSearchCondition('module_name', $name);
		}
		$count = Modules::model()->count($criteria);
		
		$pager = new CPage($count);
		$pager->pageVar = 'pageNum';
		$pager->pageSize = $numPerPage;
		$criteria->order = 'module_id asc';
		$currentPage = $pager->currentPage + 1;
		$pager->applyLimit($criteria);
		$list = Modules::model()->findAll($criteria); 
		$renderVars = array(
			'numPerPage'	=> $numPerPage,
			'list'			=> $list,
			'count'			=> $count,
			'currentPage'	=> $currentPage,
			'currentUrl'	=> CHtml::normalizeUrl(array('modules/index')),
			'name'			=> $name,
		);
		$this->render('index', $renderVars);
	}
	
	public function actionAdd() {
		if (($data = Yii::app()->request->getPost('data')) != null) {
			$currentDate  = date('Y-m-d H:i:s', time());
			$modules = new Modules;
			$modules->attributes = $data;
			$modules->createdtime = $currentDate;
			$modules->modifiedtime = $currentDate;
			$modules->createdby = Yii::app()->user->uid;
			if (!empty($_FILES['Modules']['name']['link'])) {
				$file = CUploadedFile::getInstance($modules, 'link');
				$newFileName = self::makeFileName($file->extensionName); 
				$saveDir = self::byDateMdkir(Yii::app()->params['upload_dir']).$newFileName;
				$file->saveAs($saveDir);
				$modules->link = $saveDir;
			}
			if($modules->save())
			{	
				$_REQUEST['callbackType'] = 'closeCurrent';
				$this->success('创建模块成功!');
			} else {
				foreach ($modules->errors as $error) {
					$this->error($error[0]);
				}
			}
		}
		$this->render('add');
	}
	
	private static function byDateMdkir($dir) {
		$yearDir = $dir.date('Y');
		if (!file_exists($yearDir)) {
			@mkdir($yearDir, 0777);
		}
		$monthDir = $yearDir.'/'.date('m');
		if (!file_exists($monthDir)) {
			@mkdir($monthDir, 0777);
		}
		$dayDir = $monthDir.'/'.date('d').'/';
		if (!file_exists($dayDir)) {
			@mkdir($dayDir, 0777);
		}
		return $dayDir;
	}
	
	private static function makeFileName($prefix) {
		return  md5(date('Y-m-d H:i:s', time()).rand(0, 1000000)).'.'.$prefix;
	}
	
	public function actionDel() {
		if (($id = Yii::app()->request->getQuery('id')) != null) {
			$count = Modules::model()->deleteByPk($id);
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
		if (($id = Yii::app()->request->getQuery('id')) != null) {
			$list = Modules::model()->findByPk($id);
			if (empty($list)) {
				$this->error('模块不存在！');
			}
			$this->render('edit', array('data'=>$list));
		} else if (($data = Yii::app()->request->getPost('data')) != null) {
			$list = Modules::model()->findByPk($data['module_id']);
			$modules = new Modules;
			$currentDate  = date('Y-m-d H:i:s', time());
			$data['modifiedby'] = Yii::app()->user->uid;
			$data['modifiedtime'] = $currentDate;
			if (!empty($_FILES['Modules']['name']['link'])) {
				$file = CUploadedFile::getInstance($modules, 'link');
				$newFileName = self::makeFileName($file->extensionName); 
				$saveDir = self::byDateMdkir(Yii::app()->params['upload_dir']).$newFileName;
				$file->saveAs($saveDir);
				$data['link'] = $saveDir;
				@unlink($list['link']);
			}
			
			$attributes = $data;
			$modules->updateByPk($data['module_id'], $attributes);
			foreach ($modules->errors as $error) {
				$this->error($error[0]);
			}
			$_REQUEST['callbackType'] = 'closeCurrent';
			$this->success('修改成功!');
		}
	}
	
	public function actionDetail() {
		if (($id = Yii::app()->request->getQuery('id')) != null) {
			$list = Modules::model()->findByPk($id);
			if (empty($list)) {
				$this->error('模块不存在！');
			}
			$this->render('detail', array('data'=>$list));
		}
	}
	
	public function actionListFunc() {
		if (($id = Yii::app()->request->getQuery('id')) != null) {
			$list = Func::model()->findAll('Module_ID='.$id);
			$this->render('listFunc', array('list'=>$list));
		}
	}
}