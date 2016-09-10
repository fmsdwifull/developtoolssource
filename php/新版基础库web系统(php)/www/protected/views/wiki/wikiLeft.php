<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title><?php echo Yii::app()->name; ?></title>
</head>
<body>
<table width="100%" border="0">
<tr><td valign="top">
    <table width="100%" border="0" summary="Show the index of module">
	 <?php
		foreach ($typeList as $typeKey=>$typeVal) {
	 ?>
      <tr>
        <td height = "10"></td>
      </tr>
      <tr>
        <td><strong><?php echo $typeVal;?></strong></td>
      </tr>
      <tr>
        <td><table width="100%" border="0">
          <tr>
            <td width="30">&nbsp;</td>
            <td width="170"><table width="170" border="0">
			 <?php
				foreach ($modules as $module) { 
					if ($module['type'] == $typeKey) {
			?>
              <tr>
                <td><a href="<?php echo CHtml::normalizeUrl(array('wiki/wikiMain', 'id'=>$module['module_id']))?>" target="mainFrame"><?php echo $module['module_name'];?></a></td>
              </tr>
             <?php
					}
				}  
			?>
            </table></td>
          </tr>
        </table></td>
      </tr>
	 <?php } ?>
    </table>
</td>
	<td><img src="<?php echo Yii::app()->request->baseUrl; ?>/static/images/line_y.png" width="3" style="min-height:1000px;height:auto;" /></td>
</tr>
</table>
</body>
</html>
