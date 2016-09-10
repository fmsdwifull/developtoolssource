<div class="page">
	<div class="pageContent">
		<div class="pageFormContent" layoutH="58">
			<div class="unit">
				<label>模块名称：</label>
				<?php echo $data->module_name;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>模块的类型：</label>
				<?php 
					if ($data->type  == 0) {
						echo '内存';
					} else if ($data->type  == 1) {
						echo '字符串';
					} else if ($data->type  == 2) {
						echo '网络';
					} else {
						echo '数据结构';
					}
				?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>模块描述：</label>
				<?php echo $data->desciption;?>
			</div>
			<div class="divider"></div>
			
			<div class="unit">
				<label>注意事项：</label>
				<?php echo $data->remarks;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>需要引用的头文件：</label>
				<?php echo $data->requirements;?>
			</div>
			<div class="divider"></div>
			
			<div class="unit">
				<label>文件路径名：</label>
				<a href="<?php echo $data->link;?>" target="__blank" style="color:red;">查看</a>
			</div>
			<div class="divider"></div>
			
			<div class="unit">
				<label>负责人：</label>
				<?php echo $data->supporter;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>创建时间：</label>
				<?php echo $data->createdtime;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>最后修改时间：</label>
				<?php echo $data->modifiedtime;?>
			</div>
			<div class="divider"></div>
			
			<div class="unit">
				<label>是否启用：</label>
				<?php if ($data->enabled == 1) {?><font color="green">是</font><?php } else {?><font color="red">否</font><?php } ?>
			</div>
			<div class="divider"></div>
			
		</div>
		<div class="formBar">
			<ul>
				<li><div class="button"><div class="buttonContent"><button type="button" class="close">关闭</button></div></div></li>
			</ul>
		</div>
	</div>
</div>