<?php
/**
 * 管理员管理  
 */
class UserController extends Controller
{	
	protected $navTabId = 'user_index';
	
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
			/*array('allow',  // allow all users to access 'index' and 'view' actions.
				'actions'=>array('index','view'),
				'users'=>array('*'),
			),*/
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
			$criteria->addSearchCondition('User_Name', $name);
		}
		$count = User::model()->count($criteria);
		
		$pager = new CPage($count);
		$pager->pageVar = 'pageNum';
		$pager->pageSize = $numPerPage;
		$criteria->order = 'User_ID asc';
		$currentPage = $pager->currentPage + 1;
		$pager->applyLimit($criteria);
		$userList = User::model()->findAll($criteria); 
		$renderVars = array(
			'numPerPage'	=> $numPerPage,
			'list'			=> $userList,
			'count'			=> $count,
			'currentPage'	=> $currentPage,
			'currentUrl'	=> CHtml::normalizeUrl(array('user/index')),
			'name'			=> $name,
		);
		$this->render('index', $renderVars);
	}
	
	public function actionAdd() {
		if (($data = Yii::app()->request->getPost('data')) != null) {
			$user = new User;
			$userList = $user->find('User_Name=:username', array(':username'=>$data['username']));
			if ($userList != null) {
				$this->error('该用户名已经存在！');
			}
			$date = date('Y-m-d H:i:s', time());
			$saveData = array(
				'User_Name'	=> $data['username'],
				'PassWord'	=> $user->md5Password($data['password']),
				'createdtime' => $date,
				'modifiedtime'	=> $date,
			);
			$user->attributes = $saveData;
			if($user->save())
			{	
				$_REQUEST['callbackType'] = 'closeCurrent';
				$this->success('添加成功!');
			} else {
				foreach ($user->errors as $error) {
					$this->error($error[0]);
				}
			}
		}
		$this->render('add');
	}
	
	public function actionDel() {
		if (($uid = Yii::app()->request->getQuery('id')) != null) {
			if ($uid == 1) {
				$this->error('抱歉，admin不能被删除！');
			}
			$count = User::model()->deleteByPk($uid);
			if ($count > 0) {
				$this->success('删除成功！');
			} else {
				$this->success('删除失败！');
			}
		} else {
			$this->error('数据缺失！');
		}
	}
	
	public function actionEdit() {
		if (($uid = Yii::app()->request->getQuery('id')) != null) {
			$userList = User::model()->findByPk($uid);
			if (empty($userList)) {
				$this->error('用户不存在！');
			}
			$this->render('edit', array('data'=>$userList));
		} else if (($data = Yii::app()->request->getPost('data')) != null) {
			$user = User::model();
			$attributes = array(
				'User_Name'	=> $data['username'],
				'modifiedtime'	=> date('Y-m-d H:i:s', time()),
			);
			if (!empty($data['password']))
				$attributes['password'] = $user->md5Password($data['password']);
			
			$count = $user->updateByPk($data['id'], $attributes);
			$_REQUEST['callbackType'] = 'closeCurrent';
			$this->success('修改成功!');
		}
	}
}