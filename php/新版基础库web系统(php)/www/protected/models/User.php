<?php

/**
 * This is the model class for table "user".
 *
 * The followings are the available columns in table 'user':
 * @property string $User_ID
 * @property string $User_Name
 * @property string $PassWord
 * @property string $createdtime
 */
class User extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return User the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	public function tableName()
	{
		return 'user';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('User_Name', 'length', 'max'=>50),
			array('PassWord', 'length', 'max'=>32),
			array('createdtime', 'safe'),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('User_ID, User_Name, PassWord, createdtime', 'safe', 'on'=>'search'),
		);
	}

	/**
	 * @return array relational rules.
	 */
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'User_ID' => 'User',
			'User_Name' => 'User Name',
			'PassWord' => 'Pass Word',
			'createdtime' => 'Createdtime',
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('User_ID',$this->User_ID,true);
		$criteria->compare('User_Name',$this->User_Name,true);
		$criteria->compare('PassWord',$this->PassWord,true);
		$criteria->compare('createdtime',$this->createdtime,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
	
	public function md5Password($pwd) {
		return md5($pwd);
	}
	
	public function validatePassword($password, $okPassword) {
		return $this->md5Password($password) == $okPassword;
	}
}