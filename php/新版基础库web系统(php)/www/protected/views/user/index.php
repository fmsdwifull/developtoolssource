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
					<label>用户名：</label>
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
				<li><a class="add" href="<?php echo CHtml::normalizeUrl(array('user/add'));?>" target="dialog" mask="true"><span>新增用户</span></a></li>

				<li><a class="delete" href="<?php echo Yii::app()->createUrl('user/del', array('id'=>'{tg_user}')); ?>" target="ajaxTodo" title="确定要删除该用户吗?" warn="请选择用户"><span>删除用户</span></a></li>

				<li><a class="edit" href="<?php echo Yii::app()->createUrl('user/edit', array('id'=>'{tg_user}')); ?>" target="dialog" mask="true" warn="请选择用户"><span>编辑用户</span></a></li>
			</ul>
		</div>

		<table class="list" width="100%" layoutH="116">
			<thead>
			<tr>
				<th align="center">UID</th>
				<th align="center">用户名</th>
				<th width="230" align="center">创建时间</th>
				<th width="230" align="center">-操作-</th>
			</tr>
			</thead>
			<tbody>
			<?php
				$Num = ($currentPage-1) * $numPerPage;
				foreach ($list as $k=>$v) {
					$Num++;
			?>
				<tr target="tg_user" rel="<?php echo $v['User_ID'];?>">
					
					<td align="center"><?php echo $v['User_ID'];?></td>
					<td align="center"><?php echo $v['User_Name'];?></td>
					<td align="center"><?php echo $v['createdtime'];?></td>
					<td align="center"><a class="delete" href="<?php echo Yii::app()->createUrl('user/del', array('id'=>$v['User_ID'])); ?>" target="ajaxTodo" title="确定要删除该用户吗?"><span>删除</span></a> | <a class="edit" href="<?php echo Yii::app()->createUrl('user/edit', array('id'=>$v['User_ID'])); ?>" target="dialog" mask="true"><span>编辑</span></a></td>
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