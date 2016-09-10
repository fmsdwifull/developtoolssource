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
					<label>模块名称：</label>
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
				<li><a class="add" href="<?php echo CHtml::normalizeUrl(array('modules/add'));?>" target="dialog" mask="true" width="550" height="520"><span>创建模块</span></a></li>

				<li><a class="delete" href="<?php echo Yii::app()->createUrl('modules/del', array('id'=>'{tg_modules}')); ?>" target="ajaxTodo" title="确定要删除该模块吗?" warn="请选择模块"><span>删除模块</span></a></li>

				<li><a class="edit" href="<?php echo Yii::app()->createUrl('modules/edit', array('id'=>'{tg_modules}')); ?>" target="dialog" mask="true" warn="请选择模块" width="550" height="520"><span>编辑模块</span></a></li>
			</ul>
		</div>

		<table class="list" width="100%" layoutH="116">
			<thead>
			<tr>
				<th align="center">序号</th>
				<th align="center">模块名称</th>
				<th align="center">模块类型</th>
				<th align="center">模块描述</th>
				<th align="center" width="80">负责人</th>
				<th width="80" align="center">是否启用</th>
				<th width="180" align="center">-操作-</th>
			</tr>
			</thead>
			<tbody>
			<?php
				$Num = ($currentPage-1) * $numPerPage;
				foreach ($list as $k=>$v) {
					$Num++;
			?>
				<tr target="tg_modules" rel="<?php echo $v['module_id'];?>">
					
					<td align="center"><?php echo $Num;?></td>
					<td align="center"><?php echo $v['module_name'];?></td>
					<td align="center">
					<?php 
						$type = '数据结构';
						if ($v['type'] == 0) {
							$type = '内存';
						} else if ($v['type'] == 1) {
							$type = '字符串';
						} else if ($v['type'] == 2) {
							$type = '网络';
						}

						echo $type;
					?>
					</td>
					<td align="center"><?php echo $v['desciption'];?></td>
					<td align="center"><?php echo $v['supporter'];?></td>
					<td align="center"><?php if ($v['enabled'] == 1) {?><font color="green">是</font><?php } else {?><font color="red">否</font><?php } ?></td>
					<td align="center"><a class="delete" href="<?php echo Yii::app()->createUrl('modules/del', array('id'=>$v['module_id'])); ?>" target="ajaxTodo" title="确定要删除该模块吗?"><span>删除</span></a> | <a class="edit" href="<?php echo Yii::app()->createUrl('modules/edit', array('id'=>$v['module_id'])); ?>" target="dialog" mask="true" width="550" height="520"><span>编辑</span></a> | <a class="edit" href="<?php echo Yii::app()->createUrl('modules/detail', array('id'=>$v['module_id'])); ?>" target="dialog" mask="true" width="550" height="520"><span>详情</span></a> | <a class="edit" href="<?php echo Yii::app()->createUrl('modules/listFunc', array('id'=>$v['module_id'])); ?>" target="dialog" width="1000" height="520" rel="see_listFunc"><span>查看函数</span></a></td>
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