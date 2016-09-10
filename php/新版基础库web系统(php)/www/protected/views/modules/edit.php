<div class="page">
	<div class="pageContent">
		<form method="post" action="<?php echo CHtml::normalizeUrl(array('modules/edit'));?>" enctype="multipart/form-data" onsubmit="return iframeCallback(this, dialogAjaxDone);">
			<div class="pageFormContent" layoutH="58">
				<div class="unit">
					<label>模块名称：</label>
					<input type="hidden" name="data[module_id]" value="<?php echo $data->module_id;?>"/>
					<input type="text" class="required" size="50" name="data[module_name]" value="<?php echo $data->module_name;?>"/>
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>模块的类型：</label>
					<select name="data[type]">
						<option value="0" <?php if ($data->type  == 0) {echo 'selected';}?>>内存</option>
						<option value="1" <?php if ($data->type  == 1) {echo 'selected';}?>>字符串</option>
						<option value="2" <?php if ($data->type  == 2) {echo 'selected';}?>>网络</option>
						<option value="3" <?php if ($data->type  == 3) {echo 'selected';}?>>数据结构</option>
					</select>
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>模块描述：</label>
					<textarea name="data[desciption]" cols="50" rows="3" class="textInput required"><?php echo $data->desciption;?></textarea>
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>注意事项：</label>
					<textarea name="data[remarks]" cols="50" rows="3" class="textInput"><?php echo $data->remarks;?></textarea>
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>需要引用的头文件：</label>
					<input type="text" size="50" name="data[requirements]" value="<?php echo $data->requirements;?>"/>
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>文件路径名：</label>
					<input type="file" size="26" name="Modules[link]" /><?php if ($data->link) { ?><a href="<?php echo $data->link;?>" target="__blank" style="color:red;">查看</a><?php } ?>&nbsp;需覆盖请重新上传
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>负责人：</label>
					<input type="text" size="50" name="data[supporter]" class="required" value="<?php echo $data->supporter;?>"/>
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>是否启用：</label>
					<select name="data[enabled]">
						<option value="1" <?php if ($data->enabled  == 1) {echo 'selected';}?>>是</option>
						<option value="0" <?php if ($data->enabled  == 0) {echo 'selected';}?>>否</option>
					</select>
				</div>
				<div class="divider"></div>
				
			</div>
			<div class="formBar">
				<ul>
					<li><div class="buttonActive"><div class="buttonContent"><button type="submit">提交</button></div></div></li>
					<li><div class="button"><div class="buttonContent"><button type="button" class="close">取消</button></div></div></li>
				</ul>
			</div>
		</form>
	</div>
</div>