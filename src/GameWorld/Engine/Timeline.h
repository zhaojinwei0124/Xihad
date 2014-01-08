#pragma once

namespace xihad { namespace ngn
{
	/// ʱ����
	/**
	 * ����Ϸ��ѭ���м�¼ȫ��ʱ�䣬�����ṩ���һ�θ��¼����
	 *	- ���Զ�ʱ���� @link pause() ��ͣ@endlink ����֮ͣ����Զ�֮������������ԡ�
	 *	- ���Զ�ʱ���� @link setTimeScale() ����@endlink ������֮��ÿ�ζ����������ٶȵı������и���
	 * 
	 * @author etnlGD
	 * @date 2013��12��14�� 20:27:53
	 */
	class Timeline
	{
	public:
		/**
		 * @param initTimeSeconds reset()
		 * @param singleStep setSingleStepSeconds()
		 */
		explicit Timeline(double initTimeSeconds = 0.0, double singleStep = 1./60);

		/// ����ʱ����
		/**
		 * ����֮��������¼����Ϊ 0
		 * @see getElapsedSeconds() getLastTimeChange()
		 * @param initTimeSeconds ����֮�� getElapsedSeconds() ��Ӧ��ֵ
		 */
		void reset(double initTimeSeconds);

		/// ����ʱ����
		void update(float dtRealSeconds);

		/// ȡ��������һ��ʱ���ߵ�ʱ��
		double calcDeltaSeconds(const Timeline& other) const
		{
			return mElapsedSeconds - other.mElapsedSeconds;
		}

		/// ����ʱ��������
		void setTimeScale(float scale)
		{
			mScale = scale;
		}

		/// ȡ��ʱ������
		float getTimeScale() const
		{
			return mScale;
		}

		/// ������ͣ״̬
		/**
		 * ��֮ͣ�󣬲ſ��Զ�ʱ���߲�����������Ч
		 * @see singleStep()
		 */
		void setPaused(bool puase)
		{
			mPaused = puase;
		}

		/// �ж��Ƿ���ͣ
		/**
		 * @see singleStep()
		 */
		bool isPaused() const
		{
			return mPaused;
		}

		/// ����ʱ����
		/**
		 * �൱�ڵ��� update(getSingleStepSeconds()) ����������ͣ״̬�²�������
		 * @see isPaused() getSingleStepSeconds()
		 */
		void singleStep();

		/// ���õ��β�����ʱ����
		void setSingleStepSeconds(float secs)
		{
			mSingleStepSeconds = secs;
		}

		/// ȡ�õ��β�����ʱ����
		float getSingleStepSeconds() const
		{
			return mSingleStepSeconds;
		}

		/// ȡ�����һ��ʱ����¼��
		float getLastTimeChange() const
		{
			return mDeltaSeconds;
		}

		/// ȡ�þ���������ʱ��
		double getElapsedSeconds() const 
		{
			return mElapsedSeconds;
		}

	private:
		void incSeconds(double scaledTime);

	private:
		double mElapsedSeconds;
		float mSingleStepSeconds;
		float mDeltaSeconds;
		float mScale;
		bool mPaused;
	};
}}
