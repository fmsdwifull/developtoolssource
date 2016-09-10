<div class="page">
	<div class="pageContent">
		<div class="pageFormContent" layoutH="58">

			<div class="unit">
				<label>所属模块：</label>
					<?php
						foreach ($modulesArr as $modules) {
							if ($modules['module_id'] == $data->Module_ID) {
								echo $modules['module_name'];
							}
						}
					?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>功能名称：</label>
				<?php echo $data->Function_Name;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>功能函数描述：</label>
				<?php echo $data->Desciption;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>函数参数：</label>
				<?php echo $data->Parameter;?>
			</div>
			<div class="divider"></div>
			
			<div class="unit">
				<label>函数返回值：</label>
				<?php echo $data->ReturnValue;?>
			</div>
			<div class="divider"></div>
			
			<div class="unit">
				<label>创建时间：</label>
				<?php echo $data->createdtime;?>
			</div>
			<div class="divider"></div>

			<div class="unit">
				<label>是否启用：</label>
				<?php if ($data->Enabled == 1) {?><font color="green">是</font><?php } else {?><font color="red">否</font><?php } ?>
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