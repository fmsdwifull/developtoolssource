<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title><?php echo Yii::app()->name; ?></title>
</head>
<body>
<table width="100%" border="0">
  <tr>
    <td><h1><strong><?php echo $module['module_name'];?></strong></h1></td>
  </tr>
  <tr>
    <td><?php echo $module['desciption'];?></td>
  </tr>

  <tr>
    <td><h3>下载链接：</h3></td>
  </tr>
  <tr>
    <td><a href="<?php echo $module['link'];?>" target="_blank">点击下载</a></td>
  </tr>


  <tr>
    <td><h3>函数：</h3></td>
  </tr>

  <tr>
    <td><table width="100%" border="0">
      <tr>
        <td width="30" valign="middle">&nbsp;</td>
        <td valign="middle"><table border="0">
		  <?php
			foreach ($func as $f) {
		  ?>
          <tr>
            <td><h4><?php echo $f['Function_Name'];?></h4></td>
          </tr>
          <tr>
            <td><?php echo $f['Desciption'];?></td>
          </tr>
          <tr>
            <td><h5>参数：</h5></td>
          </tr>
          <tr>
            <td><?php echo $f['Parameter'];?></td>
          </tr>
          <tr>
            <td><h5>返回值：</h5></td>
          </tr>
          <tr>
            <td><?php echo $f['ReturnValue'];?></td>
          </tr>
		  <tr>
            <td height="20"></td>
          </tr>
			<?php
			  }
			?>
        </table></td>
      </tr>
    </table></td>
  </tr>
  
  <tr>
    <td><h3>注意事项：</h3></td>
  </tr>
  <tr>
    <td><?php echo $module['remarks'];?></td>
  </tr>
  <tr>
    <td><h3>需要引用的头文件：</h3></td>
  </tr>
  <tr>
    <td><?php echo $module['requirements'];?></td>
  </tr>
  <tr>
    <td><h3>创建时间：</h3></td>
  </tr>
  <tr>
    <td><?php echo $module['createdtime'];?></td>
  </tr>
  <tr>
    <td><h3>最后修改时间：</h3></td>
  </tr>
  <tr>
    <td><?php echo $module['modifiedtime'];?></td>
  </tr>
    <tr>
    <td><h3>负责人：</h3></td>
  </tr>
  <tr>
    <td><?php echo $module['supporter'];?></td>
  </tr>
</table>
</body>
</html>