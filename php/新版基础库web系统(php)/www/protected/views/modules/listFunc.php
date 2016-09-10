<div class="page">
	
	<div class="pageContent">
		<table class="list" width="100%" layoutH="25">
			<thead>
			<tr>
				<th align="center">序号</th>
				<th align="center">所属模块</th>
				<th align="center">功能函数名</th>
				<th align="center">函数描述</th>
				<th align="center">函数参数</th>
				<th align="center">函数返回值</th>
				<th width="80" align="center">是否启用</th>
				<th width="80" align="center">操作</th>
			</tr>
			</thead>
			<tbody>
			<?php
				$Num = 0;
				foreach ($list as $k=>$v) {
					$Num++;
			?>
				<tr target="tg_func" rel="<?php echo $v['Function_ID'];?>">
					
					<td align="center"><?php echo $Num;?></td>
					<td align="center"><?php $modules = Modules::model()->find('module_id='.$v['Module_ID']);echo $modules['module_name'];?></td>
					<td align="center"><?php echo $v['Function_Name'];?></td>
					<td align="center"><?php echo $v['Desciption'];?></td>
					<td align="center"><?php echo $v['Parameter'];?></td>
					<td align="center"><?php echo $v['ReturnValue'];?></td>
					<td align="center"><?php if ($v['Enabled'] == 1) {?><font color="green">是</font><?php } else {?><font color="red">否</font><?php } ?></td>

					<td align="center"><a class="edit" href="<?php echo Yii::app()->createUrl('func/detail', array('id'=>$v['Function_ID'])); ?>" target="dialog" mask="true" width="550" height="520" rel="detail_func"><span>详情</span></a></td>
				</tr>
			<?php
				}
			?>
			</tbody>
		</table>
		<div class="panelBar">
			<div class="pages">
				<span>共<?php echo $Num;?>条</span>
			</div>
			
		</div>

	</div>
	
</div>