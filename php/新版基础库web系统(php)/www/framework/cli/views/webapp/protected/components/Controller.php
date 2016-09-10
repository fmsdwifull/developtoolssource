<?php
/**
 * Controller is the customized base controller class.
* All controller classes for this application should extend from this base class.
 */
class Controller extends CController
{
	/**
	 * @var string the default layout for the controller view. Defaults to 'column1',
	 * meaning using a single column layout. See 'protected/views/layouts/column1.php'.
	 */
	public $layout='';
	/**
	 * @var array context menu items. This property will be assigned to {@link CMenu::items}.
	 */
	public $menu=array();
	/**
	 * @var array the breadcrumbs of the current page. The value of this property will
	 * be assigned to {@link CBreadcrumbs::links}. Please refer to {@link CBreadcrumbs::links}
	 * for more details on how to specify this property.
	 */
	public $breadcrumbs=array();
	
	protected $navTabId = null;
	
	// 正确返回信息
    protected function success($message)
    {
        self::ajaxReturn($message,200);
    }
	
	// 错误返回信息
	protected function error($message)
    {
         self::ajaxReturn($message,300);
    }
	
	// ajax 返回信息
    protected function ajaxReturn($message, $status=200, $type='JSON')
    {
        $result  =  array();
		// 错误代码 200 正确 300 错误  301 会话超时
		$result['statusCode']  =  $status;
		$result['message'] =  $message;
        $result['navTabId']  =  !empty($this->navTabId) ? $this->navTabId : $_REQUEST['navTabId'];
		// 只有callbackType="forward"时需要forwardUrl值
		$result['callbackType'] = !empty($_REQUEST['callbackType']) ? $_REQUEST['callbackType'] : '';
		$result['forwardUrl'] = empty($_REQUEST['forwardUrl']) ? '' : $_REQUEST['forwardUrl'];
		
        if(strtoupper($type)=='XML'){
            // 返回xml格式数据
            header("Content-Type:text/xml; charset=utf-8");
            exit(xml_encode($result));
        }elseif(strtoupper($type)=='EVAL'){
            // 返回可执行的js脚本
            header("Content-Type:text/html; charset=utf-8");
            exit($result);
        } else {
			header("Content-Type:text/html; charset=utf-8");
            exit(json_encode($result));
		}
    }
}