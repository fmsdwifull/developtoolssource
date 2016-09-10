<form id="pagerForm" action="<?php echo $currentUrl;?>" method="post">
	<input type="hidden" name="pageNum" value="1"/>
	<input type="hidden" name="name" value="<?php echo $name; ?>"/>
</form>

<div class="page">
	<div class="pageHeader">
		<form onsubmit="return navTabSearch(this);" action="<?php echo $currentUrl;?>" method="post">
		<div class="searchBar">
			<ul class="searchContent">
				<li>
					<label>所属函数：</label>
					<select name="module_id">
						<option value="">-请选择所属模块-</option>
						<?php
							foreach ($modulesArr as $modules) {
						?>
							<option value="<?php echo $modules['module_id'];?>" <?php if ($modules['module_id'] == $module_id) {echo 'selected';}?>><?php echo $modules['module_name'];?></option>
						<?php
							}
						?>
					</select>
				</li>

				<li>
					<label>函数名称：</label>
					<input type="text" name="name" value="<?php echo $name; ?>"/>
				</li>
			</ul>
			<div class="subBar">
				<ul>
					<li><div class="buttonActive"><div class="buttonContent"><button type="submit">&nbsp;&nbsp;&nbsp;&nbsp;查询&nbsp;&nbsp;&nbsp;&nbsp;</button></div></div></li>
				</ul>
			</div>
		</div>
		</form>
	</div>
	
	<div class="pageContent">
		<div class="panelBar">
			<ul class="toolBar">
				<li><a class="add" href="<?php echo CHtml::normalizeUrl(array('func/add'));?>" target="dialog" mask="true" width="550" height="520"><span>创建函数</span></a></li>

				<li><a class="delete" href="<?php echo Yii::app()->createUrl('func/del', array('id'=>'{tg_func}')); ?>" target="ajaxTodo" title="确定要删除该函数吗?" warn="请选择函数"><span>删除函数</span></a></li>

				<li><a class="edit" href="<?php echo Yii::app()->createUrl('func/edit', array('id'=>'{tg_func}')); ?>" target="dialog" mask="true" warn="请选择函数" width="550" height="520"><span>编辑函数</span></a></li>
			</ul>
		</div>

		<table class="list" width="100%" layoutH="116">
			<thead>
			<tr>
				<th align="center">序号</th>
				<th align="center">所属模块</th>
				<th align="center">功能函数名</th>
				<th align="center">函数描述</th>
				<th align="center">函数参数</th>
				<th align="center">函数返回值</th>
				<th width="80" align="center">是否启用</th>
				<th width="130" align="center">-操作-</th>
			</tr>
			</thead>
			<tbody>
			<?php
				$Num = ($currentPage-1) * $numPerPage;
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
					<td align="center"><a class="delete" href="<?php echo Yii::app()->createUrl('func/del', array('id'=>$v['Function_ID'])); ?>" target="ajaxTodo" title="确定要删除该函数吗?"><span>删除</span></a> | <a class="edit" href="<?php echo Yii::app()->createUrl('func/edit', array('id'=>$v['Function_ID'])); ?>" target="dialog" mask="true" width="550" height="520"><span>编辑</span></a> | <a class="edit" href="<?php echo Yii::app()->createUrl('func/detail', array('id'=>$v['Function_ID'])); ?>" target="dialog" mask="true" width="550" height="520"><span>详情</span></a></td>
				</tr>
			<?php
				}
			?>
			</tbody>
		</table>

		<div class="panelBar">
			<div class="pages">
				<span>共<?php echo $count;?>条</span>
			</div>
			<div class="pagination" targetType="navTab" totalCount="<?php echo $count;?>" numPerPage="<?php echo $numPerPage;?>" pageNumShown="10" currentPage="<?php echo $currentPage;?>"></div>
		</div>

	</div>
	
</div>